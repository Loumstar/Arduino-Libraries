#include "midi.h"

double note_frequency(int n){
    return pow(2, (n - 69) / 12) * 440.0;
}

void note_off(int n, note notes[]){
    for(size_t i = 0; i < MAX_VOICES; i++){
        if((int) notes[i][0] == n){
            notes[i][0] = 0;
            notes[i][1] = 0;
            notes[i][2] = 0;
            break;
        }
    }
}

void note_on(int n, int vol, note notes[]){
    for(size_t i = 0; i < MAX_VOICES; i++){
        if(notes[i][0] == 0.0){
            notes[i][0] = n;
            notes[i][1] = note_frequency(n);
            notes[i][2] = vol / 128.0;
            break;
        }
    }
}

void handle_midi_msg(int msg[3], note notes[]){
    if(msg[0] < 0xA0){ // only handle note on/off messages
        if(msg[0] < 0x90){
            note_off(msg[1], notes);
        } else {
            note_on(msg[1], msg[2], notes);
        }
    }
}

void report_midi_change(int midi_msg[3], char arduino_msg[]){
    if(midi_msg[0] < 0xA0){ // only handle note on/off messages
        if(midi_msg[0] < 0x90){
            sprintf(
                arduino_msg, 
                "Note off: %d (%d Hz)\n", 
                midi_msg[1], 
                (int) note_frequency(midi_msg[1])
            );
        } else {
            sprintf(
                arduino_msg, 
                "Note on: %d (%d Hz), vol %d\n", 
                midi_msg[1], 
                (int) note_frequency(midi_msg[1]), 
                midi_msg[2]
            );
        }
    } else {
        sprintf(arduino_msg, "No note changes\n");
    }
}
