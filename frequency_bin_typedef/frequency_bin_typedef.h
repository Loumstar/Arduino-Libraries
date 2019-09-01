#ifdef __cplusplus
extern "C" {
#endif

#ifndef FREQUENCY_BIN_TYPEDEF_H
    #define FREQUENCY_BIN_TYPEDEF_H

    #include <math.h>
    #include <stdio.h>

    typedef double frequency_bin[3];
    #define FREQUENCY_BIN_SIZE sizeof(double) * 3

    const frequency_bin NULL_FREQ_BIN;

    void print_frequency_bin(const frequency_bin bin[], char msg[], size_t index);

#endif

#ifdef __cplusplus
}
#endif
