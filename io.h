//
// Created by Lenovo on 6/30/2026.
//

#ifndef ADC_PROJECT_IO_H
#define ADC_PROJECT_IO_H

#include <stdint.h>

struct __attribute__((__packed__))  AdcSample //128 bits ( 16 bytes)
 {
    float time_stamp; //32
    uint8_t ch_id; //8
    uint16_t  rawValue; //16
    int16_t  temp; //16
    uint8_t flags; //8
    uint32_t seq; //32
    uint8_t reserved[2]; //Additional two bytes = 16 bits

};

struct __attribute__((__packed__)) FileHeader
        {
    uint32_t magic ;
    uint16_t version;
    uint16_t channel_count;
    uint32_t record_count;
    uint32_t sample_rate;
    uint8_t reserved[8]; //64 bit additional
};

struct AdcSample * ReadADC_data(struct FileHeader * header);
#endif //ADC_PROJECT_IO_H
