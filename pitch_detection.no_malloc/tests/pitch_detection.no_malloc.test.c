#include <time.h>

#include "../pitch_detection.no_malloc.h"
#include "../../unittest/unittest.h"

bool is_power_of_two(int x){
    return (x & (x - 1)) == 0;
}

void print_frequency_bins(const frequency_bin bin[], size_t n){
    //method to print info of each frequency bin to the console
    for(size_t j = 0; j < n; j++){    
        if(!isnan(bin[j][0])){
            printf("(%.f Hz, %.2f dB, %.4f)\n", bin[j][0], bin[j][1], bin[j][2]);
        }
    }
}

complex* create_signal(const double a[3][2], double offset, size_t length){
    /*
    Method to return an array of values that make up an oscillation.
    
    The oscillation can be a combination of frequencies and volumes and are returned
    as a complex datatype with only real components, so fft can be applied to it.
    */
    complex* sample_signal = malloc(sizeof(complex) * SAMPLE_FRAMES);
    for(size_t i = 0; i < SAMPLE_FRAMES; i++){
        int sum = 0;
        for(size_t j = 0; j < length; j++){
            sum += a[j][1] * sin((double) 2 * PI * a[j][0] * i / FRAME_RATE);
        }
        sample_signal[i][0] = sum + offset;
        sample_signal[i][1] = 0;
    }
    return sample_signal;
}

int main(void){
    clock_t main_start = clock();
    clock_t start, end;

    double frequency_resolution = FRAME_RATE / SAMPLE_FRAMES;
    
    if(!is_power_of_two(SAMPLE_FRAMES)){
        printf("The number of frames in the clip must be a power of two.\n");
        return 1;
    }

    //Output basic properties of the transform.
    printf("The maximum frequency measured is %i Hz.\n", (int) FRAME_RATE / 2);
    printf("The frequency resolution is %.1f Hz.\n", frequency_resolution);
    printf("The length of the clip is %.3fs.\n\n", (double) SAMPLE_FRAMES / FRAME_RATE);

    //example basic waveform.  
    size_t a_size = 3;   
    
    double a[3][2] = {
        {125, 128},
        {250, 40},
        {510, 60}
    };

    //measure time taken to create the test signal.
    start = clock();
    complex* sample_signal = create_signal(a, 0, a_size);
    complex* copy = malloc(sizeof(complex) * SAMPLE_FRAMES);
    end = clock();

    printf("Signal created in %.3f ms.\n", (double) (end - start) / CLOCKS_PER_SEC * 1000);

    frequency_bin* notes = malloc(FREQUENCY_BIN_SIZE * NOTES_ARR_SIZE);
    double* harmonics = malloc(sizeof(double) * HARMONICS_ARR_SIZE);

    if(!sample_signal || !copy || !harmonics || !notes){
        if(sample_signal) free(sample_signal);
        if(copy) free(copy);
        if(harmonics) free(harmonics);
        if(notes) free(notes);
        return 1;
    }

    //Measure time taken to determine all possible pitches
    start = clock();
    get_pitches(sample_signal, copy, notes, harmonics);
    end = clock();

    printf("Signal analysed in %.3f ms.\n\n", (double) (end - start) / CLOCKS_PER_SEC * 1000);
    
    //Find the most probable pitch bin
    frequency_bin pitch_bin;
    get_pitch_bin(notes, pitch_bin);

    //Print the notes determined
    print_frequency_bins(notes, NOTES_ARR_SIZE);
    printf("\n");
    print_frequency_bins(&pitch_bin, 1);
    
    free(sample_signal);
    free(copy);
    free(harmonics);
    free(notes);

    double volume = pitch_bin[1];
    double pitch = pitch_bin[0];

    //Test whether pitch and volume are correct
    printf("\nAssert that pitch detected is 125 ± 2 Hz\n");
    printf("    %.f\n", pitch);
    if(assert_double_similar(pitch, 125.0, frequency_resolution / 2)){
        printf("    PASS\n\n");
    } else {
        printf("    FAIL\n\n");
        return 1;
    }

    printf("Assert that volume detected is -18.062 ± 1 dB\n");
    printf("    %.3f\n", volume);
    if(assert_double_similar(volume, 20 * log10f(128.0 / 1024.0), 1)){
        printf("    PASS\n\n");
    } else {
        printf("    FAIL\n\n");
        return 1;
    }
    
    clock_t main_end = clock();
    printf("Test completed in %.3f ms.\n", (double) (main_end - main_start) / CLOCKS_PER_SEC * 1000);
    
    return 0;
}