#include <time.h>
#include "../complex.lite.h"
#include "../../unittest/unittest.h"

bool assert_int_complex_equal(const complex z, int real, int imag){
    return creal(z) == real && cimag(z) == imag;
}

bool assert_double_complex_equal(const double_complex z, double real, double imag){
    return assert_double_equal(dcreal(z), real) 
        && assert_double_equal(dcimag(z), imag);
}

int main(void){
    complex z1 = {62, 12};
    complex z2 = {76, 93};

    double_complex z3 = {1, 2}; // 1 + 2i
    double_complex z4 = {5, 1}; // 5 + i

    complex target_1 = {41, -23};
    double_complex target_2;

    int real, imag;
    double dreal, dimag;

    clock_t start, end;
    double function_time;



    printf("1: Find the real and imaginary components of a complex number.\n");

    printf("    Assert equal 62 + 12i.\n");

    start = clock();
    real = creal(z1);
    imag = cimag(z1);
    end = clock();
    
    printf("        %d + %di\n", real, imag);
        if(assert_int_equal(real, 62) && assert_int_equal(imag, 12)){
        printf("        PASS (took %fs to execute)\n\n", (double) (end - start) / CLOCKS_PER_SEC);
    } else {
        printf("        FAIL (took %fs to execute)\n\n", (double) (end - start) / CLOCKS_PER_SEC);
        return 1;
    }



    printf("2: Set a complex number to zero.\n");

    printf("    Conjugate: Assert equal 0 + 0i.\n");

    start = clock();
    cset_to_zero(target_1);
    end = clock();

    printf("        %d + %di\n", creal(target_1), cimag(target_1));
        if(assert_int_equal(creal(target_1), 0) && assert_int_equal(cimag(target_1), 0)){
        printf("        PASS (took %fs to execute)\n\n", (double) (end - start) / CLOCKS_PER_SEC);
    } else {
        printf("        FAIL (took %fs to execute)\n\n", (double) (end - start) / CLOCKS_PER_SEC);
        return 1;
    }

    printf("3: Find the modulus of a complex number.\n");

    printf("    Conjugate: Assert equal 62 + -12i.\n");

    start = clock();
    cconj(z1, target_1);
    end = clock();

    printf("        %d + %di\n", creal(target_1), cimag(target_1));
        if(assert_int_equal(creal(target_1), 62) && assert_int_equal(cimag(target_1), -12)){
        printf("        PASS (took %fs to execute)\n\n", (double) (end - start) / CLOCKS_PER_SEC);
    } else {
        printf("        FAIL (took %fs to execute)\n\n", (double) (end - start) / CLOCKS_PER_SEC);
        return 1;
    }

    printf("    Modulus: Assert equal the square root of 3,988 = 63.151...\n");
    
    start = clock();
    real = cabs(z1);

    printf("        %.3f...\n", cabs(z1));
    if(assert_double_equal(cabs(z1), 63.151)){
        printf("        PASS (took %fs to execute)\n\n", (double) (end - start) / CLOCKS_PER_SEC);
    } else {
        printf("        FAIL (took %fs to execute)\n\n", (double) (end - start) / CLOCKS_PER_SEC);
        return 1;
    }


    printf("4: Calculate new complex numbers with basic arithmetic.\n");
    printf("    Addition by real: Assert equal 65 + 12i.\n");

    start = clock();
    cadd_by_real(z1, 3, target_1);
    end = clock();

    printf("        %d + %di\n", creal(target_1), cimag(target_1));
    if(assert_int_complex_equal(target_1, 65, 12)){
        printf("        PASS (took %fs to execute)\n\n", (double) (end - start) / CLOCKS_PER_SEC);
    } else {
        printf("        FAIL (took %fs to execute)\n\n", (double) (end - start) / CLOCKS_PER_SEC);
        return 1;
    }

    printf("    Addition: Assert equal 138 + 105i.\n");

    start = clock();
    cadd(z1, z2, target_1);
    end = clock();

    printf("        %d + %di\n", creal(target_1), cimag(target_1));
    if(assert_int_complex_equal(target_1, 138, 105)){
        printf("        PASS (took %fs to execute)\n\n", (double) (end - start) / CLOCKS_PER_SEC);
    } else {
        printf("        FAIL (took %fs to execute)\n\n", (double) (end - start) / CLOCKS_PER_SEC);
        return 1;
    }

    printf("    Subtraction by real: Assert 60 + 12i.\n");

    start = clock();
    csub_by_real(z1, 2, target_1);
    end = clock();
    
    printf("        %d + %di\n", creal(target_1), cimag(target_1));
    if(assert_int_complex_equal(target_1, 60, 12)){
        printf("        PASS (took %fs to execute)\n\n", (double) (end - start) / CLOCKS_PER_SEC);
    } else {
        printf("        FAIL (took %fs to execute)\n\n", (double) (end - start) / CLOCKS_PER_SEC);
        return 1;
    }

    printf("    Subtraction: Assert equal 14 + 81i.\n");

    start = clock();
    csub(z2, z1, target_1);
    end = clock();
    
    printf("        %d + %di\n", creal(target_1), cimag(target_1));
    if(assert_int_complex_equal(target_1, 14, 81)){
        printf("        PASS (took %fs to execute)\n\n", (double) (end - start) / CLOCKS_PER_SEC);
    } else {
        printf("        FAIL (took %fs to execute)\n\n", (double) (end - start) / CLOCKS_PER_SEC);
        return 1;
    }

    printf("    Division by real: Assert equals 31 + 6i.\n");

    start = clock();
    cdiv_by_real(z1, 2, target_1);
    end = clock();

    printf("        %d + %di\n", creal(target_1), cimag(target_1));
    if(assert_int_complex_equal(target_1, 31, 6)){
        printf("        PASS (took %fs to execute)\n\n", (double) (end - start) / CLOCKS_PER_SEC);
    } else {
        printf("        FAIL (took %fs to execute)\n\n", (double) (end - start) / CLOCKS_PER_SEC);
        return 1;
    }

    printf("    Double Multiplication: Assert equal 3 + 11i.\n");

    start = clock();
    dcmult(z3, z4, target_2);
    end = clock();

    printf("        %.0f + %.0fi\n", dcreal(target_2), dcimag(target_2));
    if(assert_double_complex_equal(target_2, 3.0, 11.0)){
        printf("        PASS (took %fs to execute)\n\n", (double) (end - start) / CLOCKS_PER_SEC);
    } else {
        printf("        FAIL (took %fs to execute)\n\n", (double) (end - start) / CLOCKS_PER_SEC);
        return 1;
    }

    printf("    Double Division by real: Assert equals 0.833 + 1.667i.\n");

    start = clock();
    dcdiv_by_real(z3, 1.2, target_2);
    end = clock();

    printf("        %.3f + %.3fi\n", dcreal(target_2), dcimag(target_2));
    if(assert_double_complex_equal(target_2, 0.833, 1.667)){
        printf("        PASS (took %fs to execute)\n\n", (double) (end - start) / CLOCKS_PER_SEC);
    } else {
        printf("        FAIL (took %fs to execute)\n\n", (double) (end - start) / CLOCKS_PER_SEC);
        return 1;
    }

    printf("    Double Division: Assert equal 0.269 + 0.346i.\n");
    
    start = clock();
    dcdiv(z3, z4, target_2);
    end = clock();

    printf("        %.3f + %.3fi\n", dcreal(target_2), dcimag(target_2));
    if(assert_double_complex_equal(target_2, 0.269, 0.346)){
        printf("        PASS (took %fs to execute)\n\n", (double) (end - start) / CLOCKS_PER_SEC);
    } else {
        printf("        FAIL (took %fs to execute)\n\n", (double) (end - start) / CLOCKS_PER_SEC);
        return 1;
    }

    printf("    Double Exponential: Assert equal -1.131 + 2.472i.\n");
    
    start = clock();
    dcexp(z3, target_2);
    end = clock();

    printf("        %.3f + %.3fi\n", dcreal(target_2), dcimag(target_2));
    if(assert_double_complex_equal(target_2, -1.131, 2.472)){
        printf("        PASS (took %fs to execute)\n\n", (double) (end - start) / CLOCKS_PER_SEC);
    } else {
        printf("        FAIL (took %fs to execute)\n\n", (double) (end - start) / CLOCKS_PER_SEC);
        return 1;
    }

    return 0;
}