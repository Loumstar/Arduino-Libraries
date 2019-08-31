#include "unittest.h"

bool assert_int_equal(int a, int b){
    return a == b;
}

bool assert_double_equal(double a, double b){
    char string1[10], string2[10];
    
    sprintf(string1, "%.5f", a);
    sprintf(string2, "%.5f", b);

    return !strcmp(string1, string2);
}

bool assert_double_similar(double a, double b, double max_difference){
    return fabs(a - b) < max_difference;
}