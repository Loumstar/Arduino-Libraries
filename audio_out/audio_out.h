#ifndef AUDIO_OUT_H

#ifndef MAX_VOICES
#define MAX_VOICES 10
#endif

#ifndef NOTE_TYPEDEF
typedef double note[3]; // first element is note number, second is frequency, third is volume
#endif

double get_chord_amplitude(double* sample, size_t frame, double f, note* notes){
    int a = 0;
    size_t j;
    for(size_t i = 0; i < MAX_VOICES; i++){
        j = notes[i][1] / f;
        a += sample[j] * notes[i][2];
    }
    return a;
}

#endif