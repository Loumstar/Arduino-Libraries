#include <time.h>

#include "../pitch_detection.h"
#include "../../int_complex/int_complex.h"
#include "../../C-UnitTest/unittest.h"

#include "../../frequency_bin_typedef/frequency_bin_typedef.h"

char msg[100];

bool is_power_of_two(int x){
    return (x & (x - 1)) == 0;
}

int_complex* create_signal(const double a[3][2], double offset, size_t length){
    /*
    Method to return an array of values that make up an oscillation.
    
    The oscillation can be a combination of frequencies and volumes and are returned
    as a int_complex datatype with only real components, so fft can be applied to it.
    */
    int_complex* frame_array = malloc(sizeof(int_complex) * PD_FRAME_ARR_SIZE);
    for(size_t i = 0; i < PD_FRAME_ARR_SIZE; i++){
        int sum = 0;
        for(size_t j = 0; j < length; j++){
            sum += a[j][1] * sin((double) 2 * M_PI * a[j][0] * i / PD_SAMPLE_RATE);
        }
        frame_array[i][0] = sum + offset;
        frame_array[i][1] = 0;
    }
    return frame_array;
}

int main(void){
    clock_t main_start = clock();
    clock_t start, end;

    double frequency_resolution = PD_SAMPLE_RATE / PD_FRAME_ARR_SIZE;
    
    if(!is_power_of_two(PD_FRAME_ARR_SIZE)){
        printf("The number of frames in the clip must be a power of two.\n");
        return 1;
    }

    //Output basic properties of the transform.
    printf("The maximum frequency measured is %i Hz.\n", (int) PD_SAMPLE_RATE / 2);
    printf("The frequency resolution is %.1f Hz.\n", frequency_resolution);
    printf("The length of the clip is %.3fs.\n\n", (double) PD_FRAME_ARR_SIZE / PD_SAMPLE_RATE);

    //example basic waveform.  
    size_t a_size = 3;   
    
    double a[3][2] = {
        {125, 128},
        {250, 40},
        {510, 60}
    };

    //measure time taken to create the test signal.
    start = clock();
    int_complex* frame_array = create_signal(a, 0, a_size);
    int_complex* copy = malloc(sizeof(int_complex) * PD_FRAME_ARR_SIZE);
    end = clock();

    printf("Signal created in %.3f ms.\n", (double) (end - start) / CLOCKS_PER_SEC * 1000);

    frequency_bin* notes = malloc(FREQUENCY_BIN_SIZE * PD_NOTES_ARR_SIZE);
    double* harmonics = malloc(sizeof(double) * PD_HARMONICS_ARR_SIZE);

    if(!frame_array || !copy || !harmonics || !notes){
        if(frame_array) free(frame_array);
        if(copy) free(copy);
        if(harmonics) free(harmonics);
        if(notes) free(notes);
        return 1;
    }

    //Measure time taken to determine all possible pitches
    start = clock();
    get_pitches(frame_array, copy, notes, harmonics);
    end = clock();

    printf("Signal analysed in %.3f ms.\n\n", (double) (end - start) / CLOCKS_PER_SEC * 1000);
    
    //Find the most probable pitch bin
    frequency_bin pitch_bin;
    get_pitch_bin(notes, pitch_bin);

    //Print the notes determined
        for(size_t i = 0; i < PD_NOTES_ARR_SIZE; i++){
        if(!isnan(notes[i][0])){
            print_frequency_bin(notes, msg, i);
            printf("%s", msg);
        }
    }
    printf("\n");
    print_frequency_bin(&pitch_bin, msg, 0);
    printf("%s", msg);
    
    free(frame_array);
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
