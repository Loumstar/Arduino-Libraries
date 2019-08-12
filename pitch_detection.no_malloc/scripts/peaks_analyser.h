#include <stdbool.h>
#include <float.h>

//Number of frames recorded per second (typically 44.1kHz for CD).
#define FRAME_RATE 2560
//The number of values each frame can take tp describe the waveform.
#define BIT_DEPTH 1024
//The number of frames in a clip. Must be a power of two.
#define CLIP_FRAMES 512
//The minimum ratio of the amplitude of a frequency, relative
//to that of similar frequencies, which would add it to the list of peaks.
#define THRESHOLD 2.5
//The size of the array used to calculate the average amplitude of frequencies
#define SAMPLE_ARR_SIZE 75

bool amplitude_is_maxima(double a0, double a1, double a2){
    return (a1 - a0 > FLT_EPSILON) && (a1 - a2 > FLT_EPSILON);
}

bool amplitude_is_above_threshold(double a, double noise){
    return a / noise > THRESHOLD || noise < FLT_EPSILON;
}

double get_amplitude(const complex z){
    return cabs(z) * 2 / CLIP_FRAMES;
}

double decibels(double v){
    //base voltage is one as the amplitude is scaled to between 0 and 1.
    return 20 * log10f(v / BIT_DEPTH);
}

double get_noise_level(int f, const complex clip[]){
    /*
    Method to determine the amplitude of frequencies surrounding the amplitude at f, or 'noise'.

    The noise is calculated by summing the amplitudes that are within the set of frequencies 
    surrounding f, and is divided by the number of amplitudes in the set.
    */
    double sum = 0;
    size_t lb, ub;
    //if the sample indices fall outside the upper bound of clip
    if(f + floor(SAMPLE_ARR_SIZE / 2) > CLIP_FRAMES){
        //use the last set of values that make a full set.
        lb = CLIP_FRAMES - SAMPLE_ARR_SIZE;
        ub = CLIP_FRAMES;
    //if the sample indices fall outside the upper bound of clip 
    } else if(f - floor(SAMPLE_ARR_SIZE / 2) < 0){
        //use the first set of values that make a full set.
        lb = 0;
        ub = SAMPLE_ARR_SIZE;
    } else {
        //else use a set where f is the middle value.
        lb = f - floor(SAMPLE_ARR_SIZE / 2);
        ub = f + floor(SAMPLE_ARR_SIZE / 2);
    }
    for(size_t i = lb; i < ub; i++){
        //sum the values
        sum += get_amplitude(clip[i]);
    }
    //divide by the size of the sample.
    return sum / SAMPLE_ARR_SIZE;
}

void get_peaks(const complex clip[], frequency_bin peaks[]){
    /*
    Method to determine the peak frequencies of a frequency spectrum.

    If the amplitude of that frequency is a local maxima and the ratio between its
    amplitude and the average amplitude of surrounding frequencies (see get_noise_level())
    is greater than the THRESHOLD then it is added to the array.
    */
    double noise, prev_amplitude;

    double amplitude = 0;
    double next_amplitude = get_amplitude(clip[1]);

    size_t i = 0;
    
    for(size_t f = 1; f < floor(CLIP_FRAMES / 2); f++){
        noise = get_noise_level(f, clip);
        
        prev_amplitude = amplitude;
        amplitude = next_amplitude;
        next_amplitude = get_amplitude(clip[f+1]);

        if(
            i < PEAKS_ARR_SIZE //avoids overfilling array and segfaults
            && amplitude > 1 //must be as signal was int type, so smallest amplitude value is 1
            && amplitude_is_maxima(prev_amplitude, amplitude, next_amplitude)
            && amplitude_is_above_threshold(amplitude, noise)
        ){
            peaks[i][0] = f * FRAME_RATE / CLIP_FRAMES;
            peaks[i][1] = decibels(amplitude);
            i++;
        }
    }
    while(i < PEAKS_ARR_SIZE){ 
        //initialises unused positions in peaks[] to a a standard form.
        memcpy(peaks[i], NULL_FREQ_BIN, FREQUENCY_BIN_SIZE);
        i++;
    }
}