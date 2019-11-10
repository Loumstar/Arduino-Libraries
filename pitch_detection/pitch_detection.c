#include "pitch_detection.h"

void get_pitches(int_complex frame[], int_complex copy[], frequency_bin notes[], double harmonics[]){
    //method that returns an array of pitch bins that are possible notes of the audio
    convert_to_frequency_domain(frame, copy, PD_FRAME_ARR_SIZE);
    get_notes(frame, notes);

    get_note_probabilities(notes, harmonics, PD_NOTES_ARR_SIZE);
}

void get_pitch_bin(frequency_bin notes[], frequency_bin pitch_bin){
    //method that returns the pitch bin with the greatest probability
    double max_p = 0;
    size_t j;

    for(size_t i = 0; i < PD_NOTES_ARR_SIZE; i++){
        if(!isnan(notes[i][2]) && notes[i][2] > max_p){
            max_p = notes[i][2];
            j = i;
        }
    }

    memcpy(pitch_bin, notes[j], FREQUENCY_BIN_SIZE);
}

double get_pitch(int_complex frame[], int_complex copy[], frequency_bin notes[], double harmonics[]){
    //method that returns the most probable pitch of the audio.
    get_pitches(frame, copy, notes, harmonics);
    
    frequency_bin bin;
    get_pitch_bin(notes, bin);

    return bin[0];
}
