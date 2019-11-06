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

    int32_t get_reharmonised_wave_amplitude(int32_t sample[], note notes[], double voice_f, size_t frame, size_t sample_frames);

#endif

#ifdef __cplusplus
}
#endif
