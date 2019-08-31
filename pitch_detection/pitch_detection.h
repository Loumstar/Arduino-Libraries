#ifdef __cplusplus
extern "C" {
#endif

#ifndef PITCH_DETECTION_H
    #define PITCH_DETECTION_H

    //C Standard Library
    #include <string.h>

    //Arduino Contributed Libraries
    #include "int_complex.h"
    #include "double_complex.h"

    //Supporting Libraries from scripts/
    #include "fourier_transform.h"
    #include "frequency_bin_typedef.h"
    #include "peaks_correlation.h"
    #include "peaks_analyser.h"

    void get_pitches(int_complex sample[], int_complex copy[], frequency_bin notes[], double harmonics[]);

    void get_pitch_bin(frequency_bin notes[], frequency_bin pitch_bin);

    double get_pitch(int_complex sample[], int_complex copy[], frequency_bin notes[], double harmonics[]);

#endif

#ifdef __cplusplus
}
#endif