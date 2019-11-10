#ifdef __cplusplus
extern "C" {
#endif

#ifndef FOURIER_TRANSFORM_H
#define FOURIER_TRANSFORM_H

    #include <stdio.h>
    #include <string.h>
    #include <stdlib.h>

    #ifndef Arduino_h
        #include "../int_complex/int_complex.h"
        #include "../double_complex/double_complex.h"
    #else
        #include "int_complex.h"
        #include "double_complex.h"
    #endif
    
    void convert_to_frequency_domain(int_complex frame[], int_complex copy[], int frame_array_size);

#endif

#ifdef __cplusplus
}
#endif
