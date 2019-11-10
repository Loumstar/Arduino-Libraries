#include "reharmoniser.h"

long double get_linear_approx(int32_t array[], double index){
    /*
    Method that returns a linear approximation of the displacement of the wave at a 
    non-integer index.

    This is done by finding the displacement of the samples the index falls between and
    approximating the displacement based on how close it is to each sample.
    */
   
    size_t index_floored = (size_t) floor(index);

    int32_t lower_sample = array[index_floored];
    int32_t upper_sample = array[index_floored + 1];

    double proportion = index - index_floored;

    return (upper_sample * proportion) + (lower_sample * (1 - proportion));
}

int32_t get_reharmonised_sample(int32_t buffer[], note notes[], double voice_f, size_t sample, size_t buffer_samples){
    /*
    Method that returns the amplitude of the reharmonised waveform at a given sample.

    The waveform works by summing the amplitudes (superposition) of the buffer running at
    different speeds to produce the waveform for each individual note frequency.
    
    The speed of the buffer is calculated by comparing the note frequency to the 
    detected voice frequency of the audio: 
    
        speed of the buffer for a given note = note frequency / voice frequency

    For example, if a note frequency is three times the voice frequency, then the
    note waveform will be the buffer played at three times the speed.

    As the buffer is looped back sample by sample, the waveform of the example note
    therefore will move 3 samples at a time:
        
        note waveform sample = buffer[ 3 * original sample ]

    This will cause the note waveform to play the buffer in a third of the time, so the
    buffer is looped repeatedly until the original buffer is looped back once at the
    normal speed.
    */

    int64_t amplitude = 0;
    double j;
    
    for(size_t i = 0; i < MAX_VOICES; i++){
        if(notes[i][0]){
            j = fmod(sample * notes[i][1] / voice_f, buffer_samples - 1);
            amplitude += (int64_t) get_linear_approx(buffer, j) * notes[i][2]; // sample (0-255) * volume (0-128)
        }
    }

    amplitude = round(amplitude / MAX_MIDI_VOLUME);
        
    return amplitude > INT32_MAX ? INT32_MAX : amplitude < INT32_MIN ? INT32_MIN : (int32_t) amplitude;
}

void reharmonise_buffer(int32_t buffer[], int32_t target[], double pitch, note notes[], size_t buffer_samples){
    for(size_t j = 0; j < buffer_samples; j++){
        target[j] = get_reharmonised_sample(buffer, notes, pitch, j, buffer_samples);
    }
}
