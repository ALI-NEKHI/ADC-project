//
// Created by Lenovo on 6/30/2026.
//

#include <stdio.h>
#include "io.h"
#include "ADC.h"
#include "stats.h"
#include <stdlib.h>
struct AdcSample * ReadADC_data(struct FileHeader * header)
{
  FILE *dataFile = fopen("adc_sensor_log.bin","rb");
  if (dataFile == NULL) // problem with file
  {
      printf("Error loading the file check file name \n");
      return NULL;
  }
    fread (header , sizeof (struct FileHeader),1,dataFile);
    if(header->record_count == 0)
    {
        printf("No data found");
        fclose(dataFile);
        return NULL;
    }
    if(header->magic != 0xADC1BEEF)
    {
        printf("Mismatch magic number");
        fclose(dataFile);
        return NULL;
    }

    struct AdcSample * sample;
    sample= malloc (header->record_count * sizeof( struct AdcSample ));//reserve
    fread(sample,sizeof( struct AdcSample ),header->record_count,dataFile);//read

    fclose(dataFile);
    return sample;
//return start location of this data in memory to the main
}

int WriteTheResult()
{
    FILE * results = fopen("results.txt","w");
    if (results == NULL) // problem with file
    {
        printf("Error loading the file check file name \n");
        return 0;//error
    }
    struct AdcSample * adcSample;
    struct FileHeader header;
    struct DataFault  dataFault [4];
    struct StatisticsData statisticsData [4];
    struct Sampling_integrity  samplingIntegrity;
    adcSample= ReadADC_data(&header);

    float * voltages = ConvertToVoltage(adcSample,header.record_count);
    for(uint32_t i=0 ; i < 10 ; i++)//testig
    {
        printf("Record %u -- Time stamp : %f --- Channel ID : %u --- Raw Value : %u  ----- Voltage : %f --- Temperature : %u  \n",i,(adcSample+i)->time_stamp ,(adcSample+i)->ch_id,(adcSample+i)->rawValue,voltages[i],(adcSample+i)->temp);

    }
    FindDataFaults(adcSample,header.record_count,dataFault);

    for(uint32_t i=0 ; i < 4 ; i++)//testig
    {
        //console
        printf("Channel %u Faults : \n " ,i);
        printf("Over voltages = %d \n",dataFault[i].over_voltages_counter);
        printf("Under voltages = %d \n",dataFault[i].under_voltages_counter);
        printf("Sensor voltages = %d \n",dataFault[i].sensor_fault_counter);
        printf("---------------------------------------------------------------\n");

        //file
        fprintf(results,"Channel %u Faults : \n " ,i);
        fprintf(results,"Over voltages = %d \n",dataFault[i].over_voltages_counter);
        fprintf(results,"Under voltages = %d \n",dataFault[i].under_voltages_counter);
        fprintf(results,"Sensor voltages = %d \n",dataFault[i].sensor_fault_counter);
        fprintf(results,"---------------------------------------------------------------\n");
    }

    GetStatisticsPerChannel(adcSample,header.record_count,statisticsData,voltages);
    Calculate_Standard_Deviation(adcSample,header.record_count,statisticsData,voltages);

    for(uint32_t i=0 ; i < 4 ; i++)//testig
    {
        printf("Channel %u Statistics : \n " ,i);
        printf("Min Voltage Value = %f \n",statisticsData[i].minVolt);
        printf("Max Voltage Value = %f\n",statisticsData[i].maxVolt);
        printf("Mean Voltage Value = %f \n",statisticsData[i].meanVolt);
        printf("Standard Dev Value = %f \n",statisticsData[i].standard_dev);
        printf("---------------------------------------------------------------\n");

        //file
        fprintf(results,"Channel %u Statistics : \n " ,i);
        fprintf(results,"Min Voltage Value = %f \n",statisticsData[i].minVolt);
        fprintf(results,"Max Voltage Value = %f\n",statisticsData[i].maxVolt);
        fprintf(results,"Mean Voltage Value = %f \n",statisticsData[i].meanVolt);
        fprintf(results,"Standard Dev Value = %f \n",statisticsData[i].standard_dev);
        fprintf(results,"---------------------------------------------------------------\n");
    }

    GetSamplingIntegrity(adcSample,header.record_count,&samplingIntegrity);

    printf("Out of order : %d ---- Missing %d  \n",samplingIntegrity.outOfOrder_count,samplingIntegrity.missing_count);
    fprintf(results,"Out of order : %d ---- Missing %d  \n",samplingIntegrity.outOfOrder_count,samplingIntegrity.missing_count);

    free(adcSample);
    free(voltages);
    return 1;
}