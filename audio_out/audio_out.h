#define MAX_VOICES 10

double playback_amplitude(double* sample, size_t frame, double f, note* notes){
    int a = 0;
    size_t j;
    for(size_t i = 0; i < MAX_VOICES; i++){
        j = notes[i][1] / f;
        a += sample[j] * notes[i][2];
    }
    return a;
}