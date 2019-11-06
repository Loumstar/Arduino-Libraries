#include <time.h>
#include <stdio.h>

#include "../int_complex.h"
#include "../../C-UnitTest/unittest.h"

char msg[100];

bool assert_int_complex_equal(const int_complex z, int real, int imag){
    return icreal(z) == real && icimag(z) == imag;
}

int main(void){
    clock_t main_start = clock();
    clock_t start, end;

    int_complex z1 = {62, 12};
    int_complex z2 = {76, 93};

    int_complex target_1 = {41, -23};

    int real, imag;
    double dreal;



    printf("1: Find the real and imaginary components of a int_complex number.\n");

    printf("    Assert equal 62 + 12i.\n");

    start = clock();
    real = icreal(z1);
    imag = icimag(z1);
    end = clock();
    
    printf("        %d + %di\n", real, imag);
        if(assert_int_equal(real, 62) && assert_int_equal(imag, 12)){
        printf("        PASS (took %.3fms to execute)\n\n", (double) (end - start) * 1000 / CLOCKS_PER_SEC);
    } else {
        printf("        FAIL (took %.3fms to execute)\n\n", (double) (end - start) * 1000 / CLOCKS_PER_SEC);
        return 1;
    }



    printf("2: Find the modulus of a int_complex number.\n");

    printf("    Modulus: Assert equal the square root of 3,988 = 63.151...\n");
    
    start = clock();
    dreal = icabs(z1);
    end = clock();

    printf("        %.3f...\n", icabs(z1));
    if(assert_double_equal(icabs(z1), 63.151)){
        printf("        PASS (took %.3fms to execute)\n\n", (double) (end - start) * 1000 / CLOCKS_PER_SEC);
    } else {
        printf("        FAIL (took %.3fms to execute)\n\n", (double) (end - start) * 1000 / CLOCKS_PER_SEC);
        return 1;
    }



    printf("3: Set the int_complex number to zero and find its conjugate.\n");

    printf("    Set to Zero: Assert equal 0 + 0i.\n");

    start = clock();
    icset_to_zero(target_1);
    end = clock();

    printf("        %d + %di\n", icreal(target_1), icimag(target_1));
        if(assert_int_equal(icreal(target_1), 0) && assert_int_equal(icimag(target_1), 0)){
        printf("        PASS (took %.3fms to execute)\n\n", (double) (end - start) * 1000 / CLOCKS_PER_SEC);
    } else {
        printf("        FAIL (took %.3fms to execute)\n\n", (double) (end - start) * 1000 / CLOCKS_PER_SEC);
        return 1;
    }

    printf("    Conjugate: Assert equal 62 + -12i.\n");

    start = clock();
    icconj(z1, target_1);
    end = clock();

    printf("        %d + %di\n", icreal(target_1), icimag(target_1));
        if(assert_int_equal(icreal(target_1), 62) && assert_int_equal(icimag(target_1), -12)){
        printf("        PASS (took %.3fms to execute)\n\n", (double) (end - start) * 1000 / CLOCKS_PER_SEC);
    } else {
        printf("        FAIL (took %.3fms to execute)\n\n", (double) (end - start) * 1000 / CLOCKS_PER_SEC);
        return 1;
    }



    printf("4: Calculate new int_complex numbers with basic arithmetic.\n");

    printf("    Addition by real: Assert equal 65 + 12i.\n");

    start = clock();
    icadd_by_real(z1, 3, target_1);
    end = clock();

    printf("        %d + %di\n", icreal(target_1), icimag(target_1));
    if(assert_int_complex_equal(target_1, 65, 12)){
        printf("        PASS (took %.3fms to execute)\n\n", (double) (end - start) * 1000 / CLOCKS_PER_SEC);
    } else {
        printf("        FAIL (took %.3fms to execute)\n\n", (double) (end - start) * 1000 / CLOCKS_PER_SEC);
        return 1;
    }

    printf("    Addition: Assert equal 138 + 105i.\n");

    start = clock();
    icadd(z1, z2, target_1);
    end = clock();

    printf("        %d + %di\n", icreal(target_1), icimag(target_1));
    if(assert_int_complex_equal(target_1, 138, 105)){
        printf("        PASS (took %.3fms to execute)\n\n", (double) (end - start) * 1000 / CLOCKS_PER_SEC);
    } else {
        printf("        FAIL (took %.3fms to execute)\n\n", (double) (end - start) * 1000 / CLOCKS_PER_SEC);
        return 1;
    }

    printf("    Subtraction by real: Assert 60 + 12i.\n");

    start = clock();
    icsub_by_real(z1, 2, target_1);
    end = clock();
    
    printf("        %d + %di\n", icreal(target_1), icimag(target_1));
    if(assert_int_complex_equal(target_1, 60, 12)){
        printf("        PASS (took %.3fms to execute)\n\n", (double) (end - start) * 1000 / CLOCKS_PER_SEC);
    } else {
        printf("        FAIL (took %.3fms to execute)\n\n", (double) (end - start) * 1000 / CLOCKS_PER_SEC);
        return 1;
    }

    printf("    Subtraction: Assert equal 14 + 81i.\n");

    start = clock();
    icsub(z2, z1, target_1);
    end = clock();
    
    printf("        %d + %di\n", icreal(target_1), icimag(target_1));
    if(assert_int_complex_equal(target_1, 14, 81)){
        printf("        PASS (took %.3fms to execute)\n\n", (double) (end - start) * 1000 / CLOCKS_PER_SEC);
    } else {
        printf("        FAIL (took %.3fms to execute)\n\n", (double) (end - start) * 1000 / CLOCKS_PER_SEC);
        return 1;
    }

    printf("    Division by real: Assert equals 31 + 6i.\n");

    start = clock();
    icdiv_by_real(z1, 2, target_1);
    end = clock();

    printf("        %d + %di\n", icreal(target_1), icimag(target_1));
    if(assert_int_complex_equal(target_1, 31, 6)){
        printf("        PASS (took %.3fms to execute)\n\n", (double) (end - start) * 1000 / CLOCKS_PER_SEC);
    } else {
        printf("        FAIL (took %.3fms to execute)\n\n", (double) (end - start) * 1000 / CLOCKS_PER_SEC);
        return 1;
    }

    clock_t main_end = clock();
    printf("Test completed in %.3f ms.\n", (double) (main_end - main_start) / CLOCKS_PER_SEC * 1000);

    return 0;
}
