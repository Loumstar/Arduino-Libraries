#include "frequency_bin_typedef.h"

const frequency_bin NULL_FREQ_BIN = {NAN, -INFINITY, NAN};

void print_frequency_bin(const frequency_bin bin[], char msg[], size_t index){  
    sprintf(msg, "(%.f Hz, %.2f dB, %.4f)\n", bin[index][0], bin[index][1], bin[index][2]);
}