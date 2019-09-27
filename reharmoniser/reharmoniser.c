#include "reharmoniser.h"

long double get_linear_approx(int32_t array[], double index){
    /*
    Method that returns a linear approximation of the displacement of the wave at a 
    non-integer index.

    This is done by finding the displacement of the frames the index falls between and
    approximating the displacement based on how close it is to each frame.
    */
   
    size_t index_floored = (size_t) floor(index);

    int32_t lower_frame = array[index_floored];
    int32_t upper_frame = array[index_floored + 1];

    double proportion = index - index_floored;

    return (upper_frame * proportion) + (lower_frame * (1 - proportion));
}

int32_t get_reharmonised_wave_amplitude(int32_t sample[], note notes[], double voice_f, size_t frame, size_t sample_frames){
    /*
    Method that returns the amplitude of the reharmonised waveform at a given frame.

    The waveform works by summing the amplitudes (superposition) of the sample running at
    different speeds to produce the waveform for each individual note frequency.
    
    The speed of the sample is calculated by comparing the note frequency to the 
    detected voice frequency of the audio: 
    
        speed of the sample for a given note = note frequency / voice frequency

    For example, if a note frequency is three times the voice frequency, then the
    note waveform will be the sample played at three times the speed.

    As the sample is looped back frame by frame, the waveform of the example note
    therefore will move 3 frames at a time:
        
        note waveform frame = sample[ 3 * original frame ]

    This will cause the note waveform to play the sample in a third of the time, so the
    sample is looped repeatedly until the original sample is looped back once at the
    normal speed.
    */

    int64_t amplitude = 0;
    double j;
    
    for(size_t i = 0; i < MAX_VOICES; i++){
        if(notes[i][0]){
            j = fmod(frame * notes[i][1] / voice_f, sample_frames - 1);
            amplitude += (int64_t) get_linear_approx(sample, j) * notes[i][2]; // Frame (0-255) * volume (0-128)
        }
    }

    amplitude = round(amplitude / MAX_MIDI_VOLUME);
        
    return amplitude > INT32_MAX ? INT32_MAX : amplitude < INT32_MIN ? INT32_MIN : (int32_t) amplitude;
}
