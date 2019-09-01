#ifdef __cplusplus
extern "C" {
#endif

#ifndef FOURIER_TRANSFORM_H
#define FOURIER_TRANSFORM_H

    #include <stdio.h>
    #include <string.h>
    #include <stdlib.h>

    #include "int_complex.h"
    #include "double_complex.h"
    
    void convert_to_frequency_domain(int_complex sample[], int_complex copy[], int sample_array_size);

#endif

#ifdef __cplusplus
}
#endif