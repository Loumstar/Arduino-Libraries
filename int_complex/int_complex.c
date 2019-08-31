#include "int_complex.h"

/*
Small script to handle int_complex arithmetic to be used on the arduino.
Built upon Loumstar/Arduino-Libraries/int_complex/int_complex.h
*/

int icreal(const int_complex z){
    return z[0];
}

int icimag(const int_complex z){
    return z[1];
}

double icabs(const int_complex z){
    return hypot((double) icreal(z), (double) icimag(z));
}

void icset_to_zero(int_complex z){
    z[0] = 0; 
    z[1] = 0;
}

void icconj(const int_complex z, int_complex target){
    target[0] = icreal(z);
    target[1] = -icimag(z);
}

void icadd_by_real(const int_complex z1, int a, int_complex target){
    target[0] = icreal(z1) + a;
    target[1] = icimag(z1);
}

void icadd(const int_complex z1, const int_complex z2, int_complex target){
    target[0] = icreal(z1) + icreal(z2);
    target[1] = icimag(z1) + icimag(z2);
}

void icsub_by_real(const int_complex z1, int a, int_complex target){
    target[0] = icreal(z1) - a;
    target[1] = icimag(z1);
}

void icsub(const int_complex z1, const int_complex z2, int_complex target){
    target[0] = icreal(z1) - icreal(z2);
    target[1] = icimag(z1) - icimag(z2);
}

void icmult(const int_complex z1, const int_complex z2, int_complex target){
    int_complex z3 = { //z3 is used so that if one of the int_complex numbers is also the target, the calculation is not affected.
        (icreal(z1) * icreal(z2)) - (icimag(z1) * icimag(z2)),
        (icreal(z1) * icimag(z2)) + (icimag(z1) * icreal(z2))
    };
    target[0] = z3[0];
    target[1] = z3[1];
}

void icdiv_by_real(const int_complex z1, int a, int_complex target){
    target[0] = icreal(z1) / a;
    target[1] = icimag(z1) / a;
}

void icdiv(const int_complex z1, const int_complex z2, int_complex target){
    /*
    z1 / z2 
    = (a+bi) / (c+di) 
    = (a+bi)(c-di) / (c+di)(c-di)
    = (a+bi)(c-di) / (c2+d2)
    = z1 * conj(z2) / hypot(z2)^2
    */
    int_complex z3;
    icconj(z2, z3);
    icmult(z1, z3, z3);
    icdiv_by_real(z3, pow(icabs(z2), 2), target);
}