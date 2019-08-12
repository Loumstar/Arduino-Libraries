#include <stdio.h>
#include <stdlib.h>

#include "../../complex.lite/complex.lite.h"

#define PI M_PI

void print_complex_array(const complex complex_arr[], size_t s){
    for(size_t j = 0; j < s; j++){
        printf("%d + %di\n", creal(complex_arr[j]), cimag(complex_arr[j]));
    }
}

void copy_signal(const complex clip[], complex copy[], size_t n){
    //method to duplicate a signal with complex typedef
    for(size_t a = 0; a < n; a++){
        memcpy(copy[a], clip[a], COMPLEX_SIZE);
    }
}
 
void fft(complex clip[], complex copy[], size_t n, size_t step){
    /*
    Method to convert a signal from time domain to frequency domain, 
    using Fast Fourier Transform.

    This method is based on the Cooley-Turkey method.

    The code uses both (int complex) and (double complex) as int uses half the memory
    of a double, however the precision of a double is required for the exponentiation.
    */
    if(step < n){
        fft(copy, clip, n, step * 2);
        fft(copy + step, clip + step, n, step * 2);
        
        double_complex dc1, dc2;
        complex t;

        for(size_t a = 0; a < n; a += step * 2){   
            dc1[0] = 0; 
            dc1[1] = -PI * a / n;
            
            dc2[0] = (double) copy[a + step][0];
            dc2[1] = (double) copy[a + step][1];
            
            dcexp(dc1, dc1);   
            dcmult(dc1, dc2, dc2);

            t[0] = (int) dc2[0];
            t[1] = (int) dc2[1];

            cadd(copy[a], t, clip[a / 2]);
            csub(copy[a], t, clip[(a + n) / 2]);
        }
    }
}

void convert_to_frequency_domain(complex clip[], complex copy[], int clip_frames){
    //copy the signal
    copy_signal(clip, copy, clip_frames);
    //runs fourier transform
    fft(clip, copy, clip_frames, 1);
    //removes offset represented by the complex value at 0 Hz
    cset_to_zero(clip[0]);
}