#ifdef __cplusplus
extern "C" {
#endif

#ifndef AUDIO_OUT_H
    #define AUDIO_OUT_H

    #include <math.h>
    #include <stdio.h>
    #include <stdint.h>
    #include <stdlib.h>

    #include "midi.h"

    int32_t combined_notes_amplitude(int32_t sample[], note notes[], double voice_f, size_t frame, size_t sample_frames);

#endif

#ifdef __cplusplus
}
#endif
