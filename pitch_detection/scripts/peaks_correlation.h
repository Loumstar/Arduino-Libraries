#include "frequency_bin_typedef.h"

#define DISTRIBUTION_SPACING 50.0
#define HARMONICS_ARR_SIZE 20
#define PEAKS_ARR_SIZE 20

#define EULER M_E

double* get_harmonics(double f){
    //method to return an array of frequencies that are harmonics of a frequency.
    double* harmonics = malloc(sizeof(double) * HARMONICS_ARR_SIZE);
    if(!harmonics) return NULL;
    
    for(size_t h = 0; h < HARMONICS_ARR_SIZE; h++){
        harmonics[h] = f * (h + 1);
    }
    return harmonics;
}

double get_correlation(double f, frequency_bin peaks[]){
    /*
    Method that returns a value that indicates how well a frequency f fits the set of peaks found.
    
    This is done by using a variation on the normal distribution, where each peak has a bell curve
    and the correlation value returned is given by the probability at that point.
    */
    double c = 0;
    for(size_t s = 0; s < PEAKS_ARR_SIZE; s++){
        if(!isnan(peaks[s][0])){
            c += pow(EULER, -1 * pow((2 * (f - peaks[s][0]) / DISTRIBUTION_SPACING), 2));
        }
    }
    return c;
}

double test_harmonics(frequency_bin peaks[], double harmonics[]){
    //method to run get_correlation() for a set of harmonics.
    double correlation = 0;
    for(size_t h = 0; h < HARMONICS_ARR_SIZE; h++){
        correlation += get_correlation(harmonics[h], peaks);
    }
    return correlation / HARMONICS_ARR_SIZE;
}

void note_probabilities(frequency_bin peaks[]){
    //method to run test_harmonics() for the harmonics of the frequency of each peak.
    double probability;
    for(int p = 0; p < PEAKS_ARR_SIZE; p++){
        if(!isnan(peaks[p][0])){
            double* harmonics = get_harmonics(peaks[p][0]);
            
            if(!harmonics) break;

            probability = test_harmonics(peaks, harmonics);
            free(harmonics);

            peaks[p][2] = probability;
        }
    }
}