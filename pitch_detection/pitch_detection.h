#ifndef PITCH_DETECTION_H
#define PITCH_DETECTION_H

#include <string.h>
#include <math.h>

#include "scripts/fourier_transform.h"
#include "scripts/peaks_correlation.h"
#include "scripts/peaks_analyser.h"

frequency_bin* get_pitches(complex clip[]){
    //method that returns an array of pitch bins that are possible notes of the audio
    convert_to_frequency_domain(clip, CLIP_FRAMES);
    frequency_bin* peaks = get_peaks(clip);
    
    if(peaks) get_note_probabilities(peaks);

    return peaks;
}

void get_pitch_bin(frequency_bin notes[], frequency_bin pitch_bin){
    //method that returns the pitch bin with the greatest probability
    double max_p = 0;
    size_t j;

    for(size_t i = 0; i < PEAKS_ARR_SIZE; i++){
        if(!isnan(notes[i][2]) && notes[i][2] > max_p){
            max_p = notes[i][2];
            j = i;
        }
    }

    memcpy(pitch_bin, notes[j], FREQUENCY_BIN_SIZE);
}

double get_pitch(complex clip[]){
    //method that returns the most probable pitch of the audio.
    frequency_bin* notes = get_pitches(clip);
    frequency_bin bin;
    get_pitch_bin(notes, bin);
    free(notes);
    return bin[0];
}

#endif