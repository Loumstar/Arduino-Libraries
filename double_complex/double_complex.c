#include "double_complex.h"

/*
Small script to handle double_complex arithmetic to be used on the arduino.
*/

typedef double double_complex[2];

double dcreal(const double_complex z){
    return z[0];
}

double dcimag(const double_complex z){
    return z[1];
}

double dcabs(const double_complex z){
    return hypot(dcreal(z), dcimag(z));
}

void dcset_zero(double_complex z){
    z[0] = 0; 
    z[1] = 0;
}

void dcconj(const double_complex z, double_complex target){
    target[0] = dcreal(z);
    target[1] = -dcimag(z);
}

void dcadd_real(const double_complex z1, double a, double_complex target){
    target[0] = dcreal(z1) + a;
    target[1] = dcimag(z1);
}

void dcadd(const double_complex z1, const double_complex z2, double_complex target){
    target[0] = dcreal(z1) + dcreal(z2);
    target[1] = dcimag(z1) + dcimag(z2);
}

void dcsub_real(const double_complex z1, double a, double_complex target){
    target[0] = dcreal(z1) - a;
    target[1] = dcimag(z1);
}

void dcsub(const double_complex z1, const double_complex z2, double_complex target){
    target[0] = dcreal(z1) - dcreal(z2);
    target[1] = dcimag(z1) - dcimag(z2);
}

void dcmult_real(const double_complex z1, double a, double_complex target){
    target[0] = dcreal(z1) * a;
    target[1] = dcimag(z1) * a;
}

void dcmult(const double_complex z1, const double_complex z2, double_complex target){
    double_complex z3 = { //z3 is used so that if one of the double_complex numbers is also the target, the calculation is not affected.
        (dcreal(z1) * dcreal(z2)) - (dcimag(z1) * dcimag(z2)),
        (dcreal(z1) * dcimag(z2)) + (dcimag(z1) * dcreal(z2))
    };
    target[0] = z3[0];
    target[1] = z3[1];
}

void dcdiv_real(const double_complex z1, double a, double_complex target){
    target[0] = dcreal(z1) / a;
    target[1] = dcimag(z1) / a;
}

void dcdiv(const double_complex z1, const double_complex z2, double_complex target){
    /*
    z1 / z2 
    = (a+bi) / (c+di) 
    = (a+bi)(c-di) / (c+di)(c-di)
    = (a+bi)(c-di) / (c2+d2)
    = z1 * conj(z2) / hypot(z2)^2
    */
    double_complex z3;
    dcconj(z2, z3);
    dcmult(z1, z3, z3);
    dcdiv_real(z3, pow(dcabs(z2), 2), target);
}

void dcexp(const double_complex z, double_complex target){
    double_complex z2 = { //z2 is used so that if one of the double_complex numbers is also the target, the calculation is not affected.
        pow(M_E, dcreal(z)) * cos(dcimag(z)),
        pow(M_E, dcreal(z)) * sin(dcimag(z))
    };
    target[0] = z2[0];
    target[1] = z2[1];
}
