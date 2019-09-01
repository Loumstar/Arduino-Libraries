#include <math.h>
#include <string.h>

#include "pitch_detection.h"
#include "int_complex.h"
#include "unittest.h"

int_complex sample_signal[PD_SAMPLE_ARR_SIZE];
int_complex sample_signal_copy[PD_SAMPLE_ARR_SIZE];

frequency_bin notes[PD_NOTES_ARR_SIZE];
double harmonics[PD_HARMONICS_ARR_SIZE];

char msg[100];

void create_signal(const double a[3][2], double offset, int_complex sample_signal[], size_t length){
    for(size_t i = 0; i < PD_SAMPLE_ARR_SIZE; i++){
        int sum = 0;
        for(size_t j = 0; j < length; j++){
            sum += a[j][1] * sin((double) 2 * M_PI * a[j][0] * i / PD_SAMPLE_RATE);
        }
        sample_signal[i][0] = sum + offset;
        sample_signal[i][1] = 0;
    }
}

void setup(void){
    Serial.begin(9600);
    while(!Serial);
}

void loop(void){
    Serial.print("Begin test\n");
    
    uint32_t main_start = micros();
    uint32_t start, end;

    double frequency_resolution = PD_SAMPLE_RATE / PD_SAMPLE_ARR_SIZE;
    
    //Output basic properties of the transform.
    sprintf(msg, "The maximum frequency measured is %i Hz.\n", (int) PD_SAMPLE_RATE / 2);
    Serial.print(msg);
    sprintf(msg, "The frequency resolution is %.1f Hz.\n", frequency_resolution);
    Serial.print(msg);
    sprintf(msg, "The length of the clip is %.3fs.\n\n", (double) PD_SAMPLE_ARR_SIZE / PD_SAMPLE_RATE);
    Serial.print(msg);

    //example basic waveform.  
    size_t a_size = 3;   
    
    double a[3][2] = {
        {125, 128},
        {250, 40},
        {510, 60}
    };

    //measure time taken to create the test signal.
    start = micros();
    create_signal(a, 0, sample_signal, a_size);
    end = micros();

    sprintf(msg, "Signal created in %.3f ms.\n", (double) (end - start) * 1000);
    Serial.print(msg);

    //Measure time taken to determine all possible pitches
    start = micros();
    get_pitches(sample_signal, sample_signal_copy, notes, harmonics);
    end = micros();

    sprintf(msg, "Signal analysed in %.3f ms.\n\n", (double) (end - start) * 1000);
    Serial.print(msg);

    //Find the most probable pitch bin
    frequency_bin pitch_bin;
    get_pitch_bin(notes, pitch_bin);

    //Print the notes determined
    for(size_t i = 0; i < PD_NOTES_ARR_SIZE; i++){
        if(!isnan(notes[i][0])){
            print_frequency_bin(notes, msg, i);
            Serial.print(msg);
        }
    }
    Serial.print("\n");
    print_frequency_bin(&pitch_bin, msg, 0);

    double volume = pitch_bin[1];
    double pitch = pitch_bin[0];

    //Test whether pitch and volume are correct
    Serial.print("\nAssert that pitch detected is 125 ± 2 Hz\n");
    
    sprintf(msg, "    %.f\n", pitch);
    Serial.print(msg);

    if(assert_double_similar(pitch, 125.0, frequency_resolution / 2)){
        Serial.print("    PASS\n\n");
    } else {
        Serial.print("    FAIL\n\n");
    }

    Serial.print("Assert that volume detected is -18.062 ± 1 dB\n");

    sprintf(msg, "    %.3f\n", volume);
    Serial.print(msg);

    if(assert_double_similar(volume, 20 * log10f(128.0 / 1024.0), 1)){
        Serial.print("    PASS\n\n");
    } else {
        Serial.print("    FAIL\n\n");
    }
    
    uint32_t main_end = micros();

    sprintf(msg, "Test completed in %.3f ms.\n", (double) (main_end - main_start) * 1000);
    Serial.print(msg);
}