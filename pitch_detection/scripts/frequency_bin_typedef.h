#ifndef FREQUENCY_BIN_TYPEDEF_H
#define FREQUENCY_BIN_TYPEDEF_H

typedef double frequency_bin[3];
#define FREQUENCY_BIN_SIZE sizeof(double) * 3

const frequency_bin NULL_FREQ_BIN = {NAN, -INFINITY, NAN};

#endif