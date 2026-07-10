//
// Created by Lenovo on 6/30/2026.
//

#include <stdint.h>
#include "io.h"
#ifndef ADC_PROJECT_ADC_H
#define ADC_PROJECT_ADC_H

struct DataFault
{
    int over_voltages_counter;
    int under_voltages_counter;
    int sensor_fault_counter;

};

struct Sampling_integrity
{
    int outOfOrder_count;
    int missing_count;
};
float * ConvertToVoltage(struct AdcSample *sample , uint32_t record_count);
void  FindDataFaults(struct AdcSample *sample , uint32_t record_count , struct DataFault dataFault[4]);
void GetSamplingIntegrity(struct AdcSample *sample , uint32_t record_count , struct Sampling_integrity * samplingIntegrity);
#endif //ADC_PROJECT_ADC_H
