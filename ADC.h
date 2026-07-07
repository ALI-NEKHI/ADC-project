//
// Created by Lenovo on 6/30/2026.
//

#include <stdint.h>
#include "io.h"
#ifndef ADC_PROJECT_ADC_H
#define ADC_PROJECT_ADC_H

float * ConvertToVoltage(struct AdcSample *sample , uint32_t record_count);
#endif //ADC_PROJECT_ADC_H
