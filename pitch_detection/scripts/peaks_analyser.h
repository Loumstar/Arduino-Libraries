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
//The smallest value for a floating point that is considered to be greater than zero.
#define FLOAT_EPSILON 0.01

bool _is_non_zero(double a){
    return a > FLOAT_EPSILON;
}

bool _is_maxima(double y0, double y1, double y2){
    return (y1 - y0 > FLOAT_EPSILON) && (y1 - y2 > FLOAT_EPSILON);
}

bool _is_above_threshold(double a, double noise){
    return a / noise > THRESHOLD || noise < FLOAT_EPSILON;
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
        sum += cabs(clip[i]);
    }
    //divide by the size of the sample.
    return sum / SAMPLE_ARR_SIZE;
}

frequency_bin* get_peaks(const complex clip[]){
    /*
    Method to determine the peak frequencies of a frequency spectrum.

    If the amplitude of that frequency is a local maxima and the ratio between its
    amplitude and the average amplitude of surrounding frequencies (see get_noise_level())
    is greater than the THRESHOLD then it is added to the array.
    */
    frequency_bin* peaks = malloc(FREQUENCY_BIN_SIZE * PEAKS_ARR_SIZE);
    if(!peaks) return NULL;
    
    double noise, amplitude;
    size_t i = 0;
    
    for(size_t f = 0; f < floor(CLIP_FRAMES / 2); f++){
        noise = get_noise_level(f, clip);
        amplitude = cabs(clip[f]);
        if(
            i < PEAKS_ARR_SIZE //avoids overfilling array and segfaults
            && _is_non_zero(amplitude) //avoids divide-by-zero errors
            && _is_maxima(cabs(clip[f-1]), amplitude, cabs(clip[f+1]))
            && _is_above_threshold(amplitude, noise)
        ){
            peaks[i][0] = (double) f * FRAME_RATE / CLIP_FRAMES;
            peaks[i][1] = decibels(amplitude * 2 / CLIP_FRAMES);
            i++;
        }
    }
    while(i < PEAKS_ARR_SIZE){ 
        //initialises unused positions in peaks[] to a a standard form.
        memcpy(peaks[i], NULL_FREQ_BIN, FREQUENCY_BIN_SIZE);
        i++;
    }
    return peaks;
}