#ifdef __cplusplus
extern "C" {
#endif


#ifndef INT_COMPLEX_H
    #define INT_COMPLEX_H

    #include <math.h>

    typedef int int_complex[2];

    #define INT_COMPLEX_SIZE sizeof(int_complex)
    

    int icreal(const int_complex z);

    int icimag(const int_complex z);


    double icabs(const int_complex z);


    void icset_to_zero(int_complex z);

    void icconj(const int_complex z, int_complex target);


    void icadd_by_real(const int_complex z1, int a, int_complex target);

    void icadd(const int_complex z1, const int_complex z2, int_complex target);


    void icsub_by_real(const int_complex z1, int a, int_complex target);

    void icsub(const int_complex z1, const int_complex z2, int_complex target);


    void icmult_by_real(const int_complex z1, int a, int_complex target);

    void icmult(const int_complex z1, const int_complex z2, int_complex target);


    void icdiv_by_real(const int_complex z1, int a, int_complex target);

    void icdiv(const int_complex z1, const int_complex z2, int_complex target);

#endif

#ifdef __cplusplus
}
#endif
