#include <stdio.h>
#include "io.h"
#include "ADC.h"
int main() {
    struct AdcSample * adcSample;
    struct FileHeader header;
    struct DataFault  dataFault [4];
    adcSample= ReadADC_data(&header);
    float * voltages = ConvertToVoltage(adcSample,header.record_count);
    for(uint32_t i=0 ; i < 10 ; i++)//testig
    {
       printf("Record %u -- Time stamp : %f --- Channel ID : %u --- Raw Value : %u  ----- Voltage : %f --- Temperature : %u  \n",i,(adcSample+i)->time_stamp ,(adcSample+i)->ch_id,(adcSample+i)->rawValue,voltages[i],(adcSample+i)->temp);
    }
    FindDataFaults(adcSample,header.record_count,dataFault);

    for(uint32_t i=0 ; i < 4 ; i++)//testig
    {
        printf("Channel %u Faults : \n " ,i);
        printf("Over voltages = %d \n",dataFault[i].over_voltages_counter);
        printf("Under voltages = %d \n",dataFault[i].under_voltages_counter);
        printf("Sensor voltages = %d \n",dataFault[i].sensor_fault_counter);
        printf("---------------------------------------------------------------\n");

    }





    return 0;
}
