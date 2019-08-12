#ifndef AUDIO_OUT_H

#ifndef MAX_VOICES
#define MAX_VOICES 10
#endif

#ifndef NOTE_TYPEDEF
typedef double note[3]; // first element is note number, second is frequency, third is volume
#endif

int get_chord_amplitude(int sample[], note* notes, double voice_f, size_t frame, size_t sample_frames){
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

    int amplitude = 0;
    size_t j;
    
    for(size_t i = 0; i < MAX_VOICES; i++){
        if(notes[i][0]){
            j = ((size_t) (frame * notes[i][1] / voice_f)) % (sample_frames - 1);
            amplitude += sample[j] * notes[i][2]; // Frame (0-256) * volume (0-1)
        }
    }
    return amplitude && 255; // && used to avoid integer overflow
}

#endif