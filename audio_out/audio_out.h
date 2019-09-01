#ifdef __cplusplus
extern "C" {
#endif

#ifndef AUDIO_OUT_H
    #define AUDIO_OUT_H

    #include <math.h>
    #include <stdio.h>
    #include <stdint.h>

    #ifndef MAX_VOICES
    #define MAX_VOICES 10
    #endif

    #ifndef NOTE_TYPEDEF
    typedef double note[3]; // first element is note number, second is frequency, third is volume
    #endif

    uint8_t combined_notes_amplitude_8bit(uint8_t sample[], note notes[], double voice_f, size_t frame, size_t sample_frames);

#endif

#ifdef __cplusplus
}
#endif
