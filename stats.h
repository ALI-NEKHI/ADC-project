//
// Created by Lenovo on 6/30/2026.
//

#ifndef ADC_PROJECT_STATS_H
#define ADC_PROJECT_STATS_H

#include "io.h"

struct StatisticsData
{
    float minVolt;
    float maxVolt;
    float meanVolt;
    float standard_dev;
};

void GetStatisticsPerChannel (struct AdcSample *sample , uint32_t record_count , struct StatisticsData statisticsData[4],float *voltages);
void Calculate_Standard_Deviation(struct AdcSample *sample , uint32_t record_count ,struct StatisticsData statisticsData[4], float *voltages);
#endif //ADC_PROJECT_STATS_H
