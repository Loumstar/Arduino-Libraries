#ifdef __cplusplus
extern "C" {
#endif

#ifndef AUDIO_OUT_H
    #define AUDIO_OUT_H

    #include <math.h>
    #include <stdio.h>
    #include <stdint.h>
    #include <stdlib.h>

    #ifndef Arduino_h
        #include "../midi/midi.h"
    #else
        #include "midi.h"
    #endif

    int32_t get_reharmonised_sample(int32_t buffer[], note notes[], double voice_f, size_t sample, size_t buffer_samples);

    void reharmonise_buffer(int32_t buffer[], int32_t target[], double pitch, note notes[], size_t buffer_samples);

#endif

#ifdef __cplusplus
}
#endif
