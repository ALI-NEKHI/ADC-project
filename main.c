#include <stdio.h>
#include "io.h"
#include "ADC.h"
int main() {
    struct AdcSample * adcSample;
    struct FileHeader header;

    adcSample= ReadADC_data(&header);

    return 0;
}
