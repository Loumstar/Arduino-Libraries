#ifdef __cplusplus
extern "C" {
#endif

#ifndef MIDI_H
    #define MIDI_H

    #include <stdio.h>

    #ifndef MAX_VOICES
    #define MAX_VOICES 10
    #endif

    #ifndef NOTE_TYPEDEF
    typedef double note[3]; // first element is note number, second is frequency, third is volume
    #endif

    void handle_midi_msg(int msg[3], note notes[]);

    void report_midi_change(int midi_msg[3], char arduino_msg[]);

#endif

#ifdef __cplusplus
}
#endif
