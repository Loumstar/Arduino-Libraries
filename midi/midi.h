#ifndef MIDI_H
#define MIDI_H

#include <SoftwareSerial.h>
#include <stdio.h>

#define LATENCY pow(10, -3) // 1 milisecond samples
#define SAMPLE_RATE 44100 // standard 44.1kHz sample rate
#define SAMPLE_FRAMES (size_t) round(SAMPLE_RATE * LATENCY)

#ifndef MAX_VOICES
#define MAX_VOICES 10
#endif

#ifndef NOTE_TYPEDEF
typedef double note[3]; // first element is note number, second is frequency, third is volume
#endif

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

void handle_midi(int msg[3], note notes[]){
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

int* read_midi(int msg[3], Stream &midiDevice){
    size_t msg_length = midiDevice.available();
    size_t i = 0;

    while(i < msg_length){
        msg[i] = midiDevice.read(); //need to check for status byte
        i++;
    }
}

#endif