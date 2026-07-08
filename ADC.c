//
// Created by Lenovo on 6/30/2026.
//

#include <malloc.h>
#include <stdio.h>
#include "ADC.h"
float * voltages;

float * ConvertToVoltage(struct AdcSample *sample , uint32_t record_count)
{
    voltages=malloc(record_count * sizeof (float));//reserve memory for voltages dynamic
    for ( uint32_t i = 0 ; i < record_count ; i ++)
    {
        voltages[i]=((sample+i)->rawValue / 4095.0f) *3.3f;
    }
    return voltages;
}

void  FindDataFaults(struct AdcSample *sample , uint32_t record_count , struct DataFault dataFault[4])
{
    for(uint32_t i =0 ; i < 4 ; i++)
    {
        dataFault[i].over_voltages_counter=0;
        dataFault[i].under_voltages_counter=0;
        dataFault[i].sensor_fault_counter=0;
    }

    for(uint32_t i =0 ; i < record_count ; i++)
    {
        uint8_t channel_id = (sample+i)->ch_id;

        if( voltages[i] <0.3f)
        {
          dataFault[channel_id].under_voltages_counter++;
        }
        if(voltages[i] > 3.0f)
        {
            dataFault[channel_id].over_voltages_counter++;
        }
        if((sample+i)->flags & 0x01) //0x00
        {
            dataFault[channel_id].sensor_fault_counter++;
        }



    }

}