#ifdef __cplusplus
extern "C" {
#endif

#ifndef PITCH_DETECTION_H
    #define PITCH_DETECTION_H

    // C Standard Library
    #include <string.h>

    // Arduino Libraries
    #ifndef Arduino_h
        #include "../int_complex/int_complex.h"
        #include "../frequency_bin_typedef/frequency_bin_typedef.h"
        #include "../fourier_transform/fourier_transform.h"
        #include "../peaks_analyser/peaks_analyser.h"
        #include "../peaks_correlation/peaks_correlation.h"
    #else
        #include "int_complex.h"
        #include "frequency_bin_typedef.h"
        #include "fourier_transform.h"
        #include "peaks_analyser.h"
        #include "peaks_correlation.h"
    #endif

    void get_pitches(int_complex frame[], int_complex copy[], frequency_bin notes[], double harmonics[]);

    void get_pitch_bin(frequency_bin notes[], frequency_bin pitch_bin);

    double get_pitch(int_complex frame[], int_complex copy[], frequency_bin notes[], double harmonics[]);

#endif

#ifdef __cplusplus
}
#endif
