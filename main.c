#include <stdio.h>
#include "io.h"
#include "ADC.h"
int main() {
    struct AdcSample * adcSample;
    struct FileHeader header;

    adcSample= ReadADC_data(&header);
    float * voltages = ConvertToVoltage(adcSample,header.record_count);
    for(uint32_t i=0 ; i < 10 ; i++)//testig
    {
       printf("Record %u -- Time stamp : %f --- Channel ID : %u --- Raw Value : %u  ----- Voltage : %f --- Temperature : %u  \n",i,(adcSample+i)->time_stamp ,(adcSample+i)->ch_id,(adcSample+i)->rawValue,voltages[i],(adcSample+i)->temp);
    }
    return 0;
}
