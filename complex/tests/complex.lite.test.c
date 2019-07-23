#include <time.h>
#include "../complex.lite.h"
#include "../../unittest/unittest.h"

bool assert_complex_equal(const complex z, double real, double imag){
    return assert_double_equal(creal(z), real) 
        && assert_double_equal(cimag(z), imag);
}

int main(void){
    const complex z1 = {1, 2}; // 1 + 2i
    const complex z2 = {5, 1}; // 5 + i

    complex result = {1, -2}; //something non-zero

    double real, imag;

    clock_t start, end;
    double function_time;



    printf("1: Find the real and imaginary components of a complex number.\n");
    
    printf("    Assert equal 1 + 2i.\n");

    start = clock();
    real = creal(z1);
    imag =  cimag(z1);
    end = clock();

    printf("        %.1f + %.1fi\n", real, imag);
    if(assert_double_equal(creal(z1), 1) && assert_double_equal(cimag(z1), 2)){
        printf("        PASS (took %fs to execute)\n\n", (double) (end - start) / CLOCKS_PER_SEC);
    } else {
        printf("        FAIL (took %fs to execute)\n\n", (double) (end - start) / CLOCKS_PER_SEC);
        return 1;
    }



    printf("2: Set a complex number to zero.\n");

    printf("    Assert equal 0 + 0i.\n");

    start = clock();
    cset_zero(result);
    end = clock();

    printf("        %.1f + %.1fi\n", creal(result), cimag(result));
    if(assert_complex_equal(result, 0, 0)){
        printf("        PASS (took %fs to execute)\n\n", (double) (end - start) / CLOCKS_PER_SEC);
    } else {
        printf("        FAIL (took %fs to execute)\n\n", (double) (end - start) / CLOCKS_PER_SEC);
        return 1;
    }



    printf("3: Find the modulus of a complex number.\n");

    printf("    Conjugate: Assert equal 1 + -2i.\n");

    start = clock();
    cconj(z1, result);
    end = clock();

    printf("        %.1f + %.1fi\n", creal(result), cimag(result));
    if(assert_double_equal(creal(result), 1) && assert_double_equal(cimag(result), -2)){
        printf("        PASS (took %fs to execute)\n\n", (double) (end - start) / CLOCKS_PER_SEC);
    } else {
        printf("        FAIL (took %fs to execute)\n\n", (double) (end - start) / CLOCKS_PER_SEC);
        return 1;
    }

    printf("    Modulus: Assert equal the square root of 5 = 2.236...\n");

    start = clock();
    real = cabs(z1);
    end = clock();

    printf("        %.3f...\n", real);
    if(assert_double_equal(cabs(z1), 2.236)){
        printf("        PASS (took %fs to execute)\n\n", (double) (end - start) / CLOCKS_PER_SEC);
    } else {
        printf("        FAIL (took %fs to execute)\n\n", (double) (end - start) / CLOCKS_PER_SEC);
        return 1;
    }

    printf("4: Calculate new complex numbers with basic arithmetic.\n");
    
    printf("    Addition by real: Assert equal 4 + 2i.\n");

    start = clock();
    cadd_real(z1, 3, result);
    end = clock();

    printf("        %.1f + %.1fi\n", creal(result), cimag(result));
    if(assert_complex_equal(result, 4, 2)){
        printf("        PASS (took %fs to execute)\n\n", (double) (end - start) / CLOCKS_PER_SEC);
    } else {
        printf("        FAIL (took %fs to execute)\n\n", (double) (end - start) / CLOCKS_PER_SEC);
        return 1;
    }

    printf("    Addition: Assert equal 6 + 3i.\n");

    start = clock();
    cadd(z1, z2, result);
    end = clock();

    printf("        %.1f + %.1fi\n", creal(result), cimag(result));
    if(assert_complex_equal(result, 6, 3)){
        printf("        PASS (took %fs to execute)\n\n", (double) (end - start) / CLOCKS_PER_SEC);
    } else {
        printf("        FAIL (took %fs to execute)\n\n", (double) (end - start) / CLOCKS_PER_SEC);
        return 1;
    }

    printf("    Subtraction by real: Assert -1 + 2i.\n");

    start = clock();
    csub_real(z1, 2, result);
    end = clock();

    printf("        %.1f + %.1fi\n", creal(result), cimag(result));
    if(assert_complex_equal(result, -1, 2)){
        printf("        PASS (took %fs to execute)\n\n", (double) (end - start) / CLOCKS_PER_SEC);
    } else {
        printf("        FAIL (took %fs to execute)\n\n", (double) (end - start) / CLOCKS_PER_SEC);
        return 1;
    }

    printf("    Subtraction: Assert equal 4 + -1i.\n");

    start = clock();
    csub(z2, z1, result);
    end = clock();

    printf("        %.1f + %.1fi\n", creal(result), cimag(result));
    if(assert_complex_equal(result, 4, -1)){
        printf("        PASS (took %fs to execute)\n\n", (double) (end - start) / CLOCKS_PER_SEC);
    } else {
        printf("        FAIL (took %fs to execute)\n\n", (double) (end - start) / CLOCKS_PER_SEC);
        return 1;
    }

    printf("    Multiplication by real: Assert equal 3 + 6i.\n");

    start = clock();
    cmult_real(z1, 3, result);
    end = clock();

    printf("        %.1f + %.1fi\n", creal(result), cimag(result));
    if(assert_complex_equal(result, 3, 6)){
        printf("        PASS (took %fs to execute)\n\n", (double) (end - start) / CLOCKS_PER_SEC);
    } else {
        printf("        FAIL (took %fs to execute)\n\n", (double) (end - start) / CLOCKS_PER_SEC);
        return 1;
    }

    printf("    Multiplication: Assert equal 3 + 11i.\n");

    start = clock();
    cmult(z1, z2, result);
    end = clock();

    printf("        %.1f + %.1fi\n", creal(result), cimag(result));
    if(assert_complex_equal(result, 3, 11)){
        printf("        PASS (took %fs to execute)\n\n", (double) (end - start) / CLOCKS_PER_SEC);
    } else {
        printf("        FAIL (took %fs to execute)\n\n", (double) (end - start) / CLOCKS_PER_SEC);
        return 1;
    }

    printf("    Division by real: Assert equals 0.833 + 1.667i.\n");

    start = clock();
    cdiv_real(z1, 1.2, result);
    end = clock();

    printf("        %.3f + %.3fi\n", creal(result), cimag(result));
    if(assert_complex_equal(result, 0.833, 1.667)){
        printf("        PASS (took %fs to execute)\n\n", (double) (end - start) / CLOCKS_PER_SEC);
    } else {
        printf("        FAIL (took %fs to execute)\n\n", (double) (end - start) / CLOCKS_PER_SEC);
        return 1;
    }

    printf("    Division: Assert equal 0.269 + 0.346i.\n");

    start = clock();
    cdiv(z1, z2, result);
    end = clock();

    printf("        %.3f + %.3fi\n", creal(result), cimag(result));
    if(assert_complex_equal(result, 0.269, 0.346)){
        printf("        PASS (took %fs to execute)\n\n", (double) (end - start) / CLOCKS_PER_SEC);
    } else {
        printf("        FAIL (took %fs to execute)\n\n", (double) (end - start) / CLOCKS_PER_SEC);
        return 1;
    }

    printf("    Exponential: Assert equal -1.131 + 2.472i.\n");

    start = clock();
    cexp(z1, result);
    end = clock();

    printf("        %.3f + %.3fi\n", creal(result), cimag(result));
    if(assert_complex_equal(result, -1.131, 2.472)){
        printf("        PASS (took %fs to execute)\n\n", (double) (end - start) / CLOCKS_PER_SEC);
    } else {
        printf("        FAIL (took %fs to execute)\n\n", (double) (end - start) / CLOCKS_PER_SEC);
        return 1;
    }

    return 0;
}