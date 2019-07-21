#include "../complex.lite.h"
#include "../../unittest/unittest.h"

bool assert_complex_equal(const complex z, double real, double imag){
    return assert_double_equal(creal(z), real) 
        && assert_double_equal(cimag(z), imag);
}

int main(void){
    complex z1 = {1, 2}; // 1 + 2i
    complex z2 = {5, 1}; // 5 + i

    complex result;

    printf("1: Find the real and imaginary components of a complex number.\n");
    printf("    Assert equal 1 + 2i.\n");
    
    printf("        %.1f + %.1fi\n", creal(z1), cimag(z1));
        if(assert_double_equal(creal(z1), 1) && assert_double_equal(cimag(z1), 2)){
        printf("        PASS\n\n");
    } else {
        printf("        FAIL\n\n");
        return 1;
    }

    printf("2: Find the modulus of a complex number.\n");

    printf("    Conjugate: Assert equal 1 + -2i.\n");

    cconj(z1, result);
    printf("        %.1f + %.1fi\n", creal(result), cimag(result));
        if(assert_double_equal(creal(result), 1) && assert_double_equal(cimag(result), -2)){
        printf("        PASS\n\n");
    } else {
        printf("        FAIL\n\n");
        return 1;
    }

    printf("    Modulus: Assert equal the square root of 5 = 2.236...\n");
    
    printf("        %.3f...\n", cabs(z1));
    if(assert_double_equal(cabs(z1), 2.236)){
        printf("        PASS\n\n");
    } else {
        printf("        FAIL\n\n");
        return 1;
    }


    printf("3: Calculate new complex numbers with basic arithmetic.\n");
    printf("    Addition by real: Assert equal 4 + i.\n");

    cadd_by_real(z1, 3, result);
    printf("        %.1f + %.1fi\n", creal(result), cimag(result));
    if(assert_complex_equal(result, 4, 2)){
        printf("        PASS\n\n");
    } else {
        printf("        FAIL\n\n");
        return 1;
    }

    printf("    Addition: Assert equal 6 + 3i.\n");

    cadd(z1, z2, result);
    printf("        %.1f + %.1fi\n", creal(result), cimag(result));
    if(assert_complex_equal(result, 6, 3)){
        printf("        PASS\n\n");
    } else {
        printf("        FAIL\n\n");
        return 1;
    }

    printf("    Subtraction by real: Assert -1 + 2i.\n");

    csub_by_real(z1, 2, result);
    printf("        %.1f + %.1fi\n", creal(result), cimag(result));
    if(assert_complex_equal(result, -1, 2)){
        printf("        PASS\n\n");
    } else {
        printf("        FAIL\n\n");
        return 1;
    }

    printf("    Subtraction: Assert equal 4 + -1i.\n");

    csub(z2, z1, result);
    printf("        %.1f + %.1fi\n", creal(result), cimag(result));
    if(assert_complex_equal(result, 4, -1)){
        printf("        PASS\n\n");
    } else {
        printf("        FAIL\n\n");
        return 1;
    }

    printf("    Multiplication: Assert equal 3 + 11i.\n");

    cmult(z1, z2, result);
    printf("        %.1f + %.1fi\n", creal(result), cimag(result));
    if(assert_complex_equal(result, 3, 11)){
        printf("        PASS\n\n");
    } else {
        printf("        FAIL\n\n");
        return 1;
    }

    printf("    Division by real: Assert equals 0.833 + 1.667i.\n");

    cdiv_by_real(z1, 1.2, result);
    printf("        %.3f + %.3fi\n", creal(result), cimag(result));
    if(assert_complex_equal(result, 0.833, 1.667)){
        printf("        PASS\n\n");
    } else {
        printf("        FAIL\n\n");
        return 1;
    }

    printf("    Division: Assert equal 0.269 + 0.346i.\n");
    
    cdiv(z1, z2, result);
    printf("        %.3f + %.3fi\n", creal(result), cimag(result));
    if(assert_complex_equal(result, 0.269, 0.346)){
        printf("        PASS\n\n");
    } else {
        printf("        FAIL\n\n");
        return 1;
    }

    printf("    Exponential: Assert equal -1.131 + 2.472i.\n");
    
    cexp(z1, result);
    printf("        %.3f + %.3fi\n", creal(result), cimag(result));
    if(assert_complex_equal(result, -1.131, 2.472)){
        printf("        PASS\n\n");
    } else {
        printf("        FAIL\n\n");
        return 1;
    }

    return 0;
}