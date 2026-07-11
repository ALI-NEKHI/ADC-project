#include <stdio.h>
#include "io.h"
#include "ADC.h"
#include "stats.h"

int main() {

    int status= WriteTheResult();
    if(status==1)
    {
        printf("File written successfully");

    }


    return 0;
}
