#ifdef __cplusplus
extern "C" {
#endif

#ifndef DOUBLE_COMPLEX_H
    #define DOUBLE_COMPLEX_H

    #include <math.h>

    typedef double double_complex[2];

    #define DOUBLE_COMPLEX_SIZE sizeof(double_complex)

    double dcreal(const double_complex z);
    double dcimag(const double_complex z);
    
    double dcabs(const double_complex z);

    void dcset_zero(double_complex z);

    void dcconj(const double_complex z, double_complex target);

    void dcadd_real(const double_complex z1, double a, double_complex target);
    void dcadd(const double_complex z1, const double_complex z2, double_complex target);

    void dcsub_real(const double_complex z1, double a, double_complex target);
    void dcsub(const double_complex z1, const double_complex z2, double_complex target);

    void dcmult_real(const double_complex z1, double a, double_complex target);
    void dcmult(const double_complex z1, const double_complex z2, double_complex target);

    void dcdiv_real(const double_complex z1, double a, double_complex target);
    void dcdiv(const double_complex z1, const double_complex z2, double_complex target);

    void dcexp(const double_complex z, double_complex target);

#endif

#ifdef __cplusplus
}
#endif
