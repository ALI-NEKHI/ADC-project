//
// Created by Lenovo on 6/30/2026.
//

#include <stdio.h>
#include "io.h"
#include <stdlib.h>
struct AdcSample * ReadADC_data(struct FileHeader * header)
{
  FILE *dataFile = fopen("adc_sensor_log.bin","rb");
  if (dataFile == NULL) // problem with file
  {
      printf("Error loading the file check file name \n");
      return NULL;
  }
    fread (header , sizeof (struct FileHeader),1,dataFile);
    if(header->record_count == 0)
    {
        printf("No data found");
        fclose(dataFile);
        return NULL;
    }
    if(header->magic != 0xADC1BEEF)
    {
        printf("Mismatch magic number");
        fclose(dataFile);
        return NULL;
    }

    struct AdcSample * sample;
    sample= malloc (header->record_count * sizeof( struct AdcSample ));//reserve
    fread(sample,sizeof( struct AdcSample ),header->record_count,dataFile);//read

    fclose(dataFile);
    return sample;
//return start location of this data in memory to the main
}
