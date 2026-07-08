//
// Created by Lenovo on 6/30/2026.
//

#include "stats.h"
void GetStatisticsPerChannel (struct AdcSample *sample , uint32_t record_count ,  struct StatisticsData statisticsData[4],float * voltages)
{
    for(uint32_t i =0 ; i < 4 ; i++)
    {
         statisticsData[i].minVolt=3.3;
         statisticsData[i].maxVolt=0;
    }
    for(uint32_t i =0 ; i < record_count ; i++) {
        uint8_t channel_id = (sample + i)->ch_id;

        if(voltages[i] > statisticsData[channel_id].maxVolt)
        {
        }

        if(voltages[i] < statisticsData[channel_id].minVolt)
        {
        }


    }

}
