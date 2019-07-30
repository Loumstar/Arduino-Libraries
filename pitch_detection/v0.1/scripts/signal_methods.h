#include <complex.h>

//Number of frames recorded per second (typically 44.1kHz for CD).
#define FRAME_RATE 8192
//The number of values each frame can take tp describe the waveform.
#define BIT_DEPTH 1024
//The number of frames in a clip. Must be a power of two.
#define CLIP_FRAMES (int) pow(2, 12)

double mean(double complex arr[], size_t length){
    double sum = 0;
    //sum the amplitude of each frame in the clip.
    for(size_t i = 0; i < length; i++){
        sum += arr[i];
    }
    //divide by the number of frames in the clip.
    return (double) sum / length;
}

void remove_offset(double complex clip[], double offset){
    //for each frame, subtract the mean amplitude of the wave
    //and divide by the BIT_DEPTH so -0.5 < clip[i] < 0.5
    for(size_t i = 0; i < CLIP_FRAMES; i++){
        clip[i] = (clip[i] - offset) / BIT_DEPTH;
    }
}

bool is_power_of_two(int x){
    return (x & (x - 1)) == 0;
}