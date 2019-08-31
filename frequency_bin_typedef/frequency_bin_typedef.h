#ifdef __cplusplus
extern "C" {
#endif

#ifndef FREQUENCY_BIN_TYPEDEF_H
    #define FREQUENCY_BIN_TYPEDEF_H

    #include <math.h>
    #include <stdio.h>

    typedef double frequency_bin[3];
    #define FREQUENCY_BIN_SIZE sizeof(double) * 3

    extern const frequency_bin NULL_FREQ_BIN;

    inline void print_frequency_bin(const frequency_bin bin[], size_t index, char msg[]){  
        sprintf("(%.f Hz, %.2f dB, %.4f)\n", msg, bin[index][0], bin[index][1], bin[index][2]);
    }

#endif

#ifdef __cplusplus
}
#endif