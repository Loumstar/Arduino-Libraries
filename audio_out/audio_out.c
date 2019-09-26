#include "audio_out.h"

double get_linear_approx(int32_t array[], double index){
    
    
    int32_t lower_bound = array[(size_t) floor(index)];
    int32_t upper_bound = array[(size_t) floor(index) + 1];

    double proportion = index - floor(index);

    return (upper_bound * proportion) + (lower_bound * (1 - proportion));
}

int32_t combined_notes_amplitude(int32_t sample[], note notes[], double voice_f, size_t frame, size_t sample_frames){
    /*
    Method that returns the amplitude of the waveform at a given frame for all of the
    combined notes.

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
    int numberof_voices = 0;
    double j;
    
    for(size_t i = 0; i < MAX_VOICES; i++){
        if(notes[i][0]){
            j = fmod(frame * notes[i][1] / voice_f, sample_frames - 1);
            amplitude += (int64_t) get_linear_approx(sample, j) * notes[i][2]; // Frame (0-255) * volume (0-128)
            numberof_voices++;
        }
    }

    amplitude = round(amplitude / MAX_MIDI_VOLUME);
    
    return llabs(amplitude) > INT32_MAX ? INT32_MAX : (int32_t) amplitude;
}
