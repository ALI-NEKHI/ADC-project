//
// Created by Lenovo on 6/30/2026.
//

#include <malloc.h>
#include <stdio.h>
#include "ADC.h"

float * ConvertToVoltage(struct AdcSample *sample , uint32_t record_count)
{
    float * voltages;
    voltages=malloc(record_count * sizeof (float));//reserve memory for voltages dynamic
    for ( uint32_t i = 0 ; i < record_count ; i ++)
    {
        voltages[i]=(sample[i].rawValue / 4095.0f) *3.3f;
    }
    return voltages;
}