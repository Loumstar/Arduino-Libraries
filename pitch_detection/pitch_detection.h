#include <stdbool.h>
#include <string.h>
#include "scripts/fourier_transform.h"
#include "scripts/peaks_correlation.h"
#include "scripts/peaks_analyser.h"

void _convert_to_frequency_domain(complex clip[]){
    //runs fourier transform
    fft(clip, CLIP_FRAMES);
    //removes offset represented by the complex value at 0 Hz.
    cset_to_zero(clip[0]);
}

frequency_bin* get_pitches(complex clip[]){
    //method to 
    _convert_to_frequency_domain(clip);
    frequency_bin* peaks = get_peaks(clip);
    if(peaks){
        note_probabilities(peaks);
    }
    return peaks;
}

void get_pitch_bin(frequency_bin notes[], frequency_bin pitch_bin){
    double max_p = 0;

    for(size_t i = 0; i < PEAKS_ARR_SIZE; i++){
        if(!isnan(notes[i][2]) && notes[i][2] > max_p){
            memcpy(pitch_bin, notes[i], FREQUENCY_BIN_SIZE);
            max_p = notes[i][2];
        }
    }
}

double get_pitch(complex clip[]){
    frequency_bin* notes = get_pitches(clip);
    frequency_bin bin;
    get_pitch_bin(notes, bin);
    free(notes);
    return bin[0];
}