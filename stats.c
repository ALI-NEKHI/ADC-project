//
// Created by Lenovo on 6/30/2026.
//

#include "stats.h"
#include "math.h"
void GetStatisticsPerChannel (struct AdcSample *sample , uint32_t record_count ,  struct StatisticsData statisticsData[4],float * voltages)
{
    float total_voltages [4]={0,0,0,0};
    int count_voltages [4]={0,0,0,0};
    for(uint32_t i =0 ; i < 4 ; i++)
    {
         statisticsData[i].minVolt=3.3;
         statisticsData[i].maxVolt=0;
         statisticsData[i].meanVolt=0;
         statisticsData[i].standard_dev=0;
    }
    for(uint32_t i =0 ; i < record_count ; i++) {
        uint8_t channel_id = (sample + i)->ch_id;

        if(voltages[i] > statisticsData[channel_id].maxVolt)
        {
            statisticsData[channel_id].maxVolt=voltages[i];
        }

        if(voltages[i] < statisticsData[channel_id].minVolt)
        {
            statisticsData[channel_id].minVolt=voltages[i];
        }

        total_voltages[channel_id] = total_voltages[channel_id] + voltages[i];
        count_voltages[channel_id]++;

    }
    for(uint32_t i =0 ; i < 4 ; i++)
    {
        statisticsData[i].meanVolt=total_voltages[i]/count_voltages[i];
    }



}

void Calculate_Standard_Deviation(struct AdcSample *sample , uint32_t record_count ,struct StatisticsData statisticsData[4], float *voltages)
{
    float differnce=0;
    float difference_squares=0;
    float total_difference_squares[4]={0,0,0,0};
    int count_voltages [4]={0,0,0,0};

    for(uint32_t i =0 ; i < record_count ; i++) {
        uint8_t channel_id = (sample + i)->ch_id;
        differnce = voltages[i] - statisticsData[channel_id].meanVolt;
        difference_squares =differnce * differnce;
        total_difference_squares[channel_id] = total_difference_squares[channel_id]+difference_squares;
        count_voltages[channel_id]++;
    }
    for(uint32_t i =0 ; i < 4 ; i++)
    {
        float var=total_difference_squares[i]/count_voltages[i];
        statisticsData[i].standard_dev=sqrt(var);
    }
}

