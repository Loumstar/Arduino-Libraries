#include "frequency_bin_typedef.h"

#define DISTRIBUTION_SPACING 50.0
#define HARMONICS_ARR_SIZE 20

#define EULER M_E

void get_harmonics(double f, double harmonics[]){
    //method to return an array of frequencies that are harmonics of a frequency.
    for(size_t h = 0; h < HARMONICS_ARR_SIZE; h++){
        harmonics[h] = f * (h + 1);
    }
}

double get_correlation(double f, frequency_bin peaks[], size_t notes_array_size){
    /*
    Method that returns a value that indicates how well a frequency f fits the set of peaks found.
    
    This is done by using a variation on the normal distribution, where each peak has a bell curve
    and the correlation value returned is given by the probability at that point.
    */
    double c = 0;
    for(size_t s = 0; s < notes_array_size; s++){
        if(!isnan(peaks[s][0])){
            c += pow(EULER, -1 * pow((2 * (f - peaks[s][0]) / DISTRIBUTION_SPACING), 2));
        }
    }
    return c;
}

double test_harmonics(frequency_bin peaks[], double harmonics[], size_t notes_array_size){
    //method to run get_correlation() for a set of harmonics.
    double correlation = 0;
    for(size_t h = 0; h < HARMONICS_ARR_SIZE; h++){
        correlation += get_correlation(harmonics[h], peaks, notes_array_size);
    }
    return correlation / HARMONICS_ARR_SIZE;
}

void get_note_probabilities(frequency_bin peaks[], double harmonics[], size_t notes_array_size){
    /*
    Method that adds the probability of a frequency bin being the 'note' of the audio
    to the last column in the frequency bin array.

    This is done by determining the harmonics of the frequency bin and comparing how well
    they fit all the peaks in the spectrum.
    */
    double probability;
    for(int p = 0; p < notes_array_size; p++){
        if(!isnan(peaks[p][0])){
            get_harmonics(peaks[p][0], harmonics);

            probability = test_harmonics(peaks, harmonics, notes_array_size);
            peaks[p][2] = probability;
        }
    }
}