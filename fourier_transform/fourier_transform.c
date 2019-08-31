#include "fourier_transform.h"

void copy_signal(const int_complex sample[], int_complex copy[], size_t n){
    //method to duplicate a signal with int_complex typedef
    for(size_t a = 0; a < n; a++){
        memcpy(copy[a], sample[a], INT_COMPLEX_SIZE);
    }
}
 
void fft(int_complex sample[], int_complex copy[], size_t n, size_t step){
    /*
    Method to convert a signal from time domain to frequency domain, 
    using Fast Fourier Transform.

    This method is based on the Cooley-Turkey method.

    The code uses both (int int_complex) and (double int_complex) as int uses half the memory
    of a double, however the precision of a double is required for the exponentiation.
    */
    if(step < n){
        fft(copy, sample, n, step * 2);
        fft(copy + step, sample + step, n, step * 2);
        
        double_complex dc1, dc2;
        int_complex t;

        for(size_t a = 0; a < n; a += step * 2){   
            dc1[0] = 0; 
            dc1[1] = -M_PI * a / n;
            
            dc2[0] = (double) copy[a + step][0];
            dc2[1] = (double) copy[a + step][1];
            
            dcexp(dc1, dc1);   
            dcmult(dc1, dc2, dc2);

            t[0] = (int) dc2[0];
            t[1] = (int) dc2[1];

            icadd(copy[a], t, sample[a / 2]);
            icsub(copy[a], t, sample[(a + n) / 2]);
        }
    }
}

void convert_to_frequency_domain(int_complex sample[], int_complex copy[], int sample_array_size){
    //copy the signal
    copy_signal(sample, copy, sample_array_size);
    //runs fourier transform
    fft(sample, copy, sample_array_size, 1);
    //removes offset represented by the int_complex value at 0 Hz
    icset_to_zero(sample[0]);
}