#ifdef __cplusplus
extern "C" {
#endif

#ifndef PEAKS_CORRELATION_H
    #define PEAKS_CORRELATION_H

    #include <math.h>

    #ifndef Arduino_h
        #include "../frequency_bin_typedef/frequency_bin_typedef.h"
    #else
        #include "frequency_bin_typedef.h"
    #endif

    #define PD_NORMAL_DIST_WIDTH 100.0
    #define PD_HARMONICS_ARR_SIZE 20

    void get_note_probabilities(frequency_bin peaks[], double harmonics[], size_t notes_array_size);

#endif

#ifdef __cplusplus
}
#endif
