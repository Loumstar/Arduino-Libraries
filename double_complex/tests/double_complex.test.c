#include <time.h>
#include <stdio.h>

#include "double_complex.h"
#include "unittest.h"

bool assert_complex_equal(const double_complex z, double real, double imag){
    return assert_double_equal(dcreal(z), real) 
        && assert_double_equal(dcimag(z), imag);
}

int main(void){
    clock_t main_start = clock();
    clock_t start, end;

    const double_complex z1 = {1, 2}; // 1 + 2i
    const double_complex z2 = {5, 1}; // 5 + i

    double_complex result = {1, -2}; //something non-zero

    double real, imag;



    printf("1: Find the real and imaginary components of a double_complex number.\n");
    
    printf("    Assert equal 1 + 2i.\n");

    start = clock();
    real = dcreal(z1);
    imag =  dcimag(z1);
    end = clock();

    printf("        %.1f + %.1fi\n", real, imag);
    if(assert_double_equal(dcreal(z1), 1) && assert_double_equal(dcimag(z1), 2)){
        printf("        PASS (took %.3fms to execute)\n\n", (double) (end - start) * 1000 / CLOCKS_PER_SEC);
    } else {
        printf("        FAIL (took %.3fms to execute)\n\n", (double) (end - start) * 1000 / CLOCKS_PER_SEC);
        return 1;
    }



    printf("2: Set a double_complex number to zero.\n");

    printf("    Assert equal 0 + 0i.\n");

    start = clock();
    dcset_zero(result);
    end = clock();

    printf("        %.1f + %.1fi\n", dcreal(result), dcimag(result));
    if(assert_complex_equal(result, 0, 0)){
        printf("        PASS (took %.3fms to execute)\n\n", (double) (end - start) * 1000 / CLOCKS_PER_SEC);
    } else {
        printf("        FAIL (took %.3fms to execute)\n\n", (double) (end - start) * 1000 / CLOCKS_PER_SEC);
        return 1;
    }



    printf("3: Find the modulus of a double_complex number.\n");

    printf("    Conjugate: Assert equal 1 + -2i.\n");

    start = clock();
    dcconj(z1, result);
    end = clock();

    printf("        %.1f + %.1fi\n", dcreal(result), dcimag(result));
    if(assert_double_equal(dcreal(result), 1) && assert_double_equal(dcimag(result), -2)){
        printf("        PASS (took %.3fms to execute)\n\n", (double) (end - start) * 1000 / CLOCKS_PER_SEC);
    } else {
        printf("        FAIL (took %.3fms to execute)\n\n", (double) (end - start) * 1000 / CLOCKS_PER_SEC);
        return 1;
    }

    printf("    Modulus: Assert equal the square root of 5 = 2.236...\n");

    start = clock();
    real = dcabs(z1);
    end = clock();

    printf("        %.3f...\n", real);
    if(assert_double_equal(dcabs(z1), 2.236)){
        printf("        PASS (took %.3fms to execute)\n\n", (double) (end - start) * 1000 / CLOCKS_PER_SEC);
    } else {
        printf("        FAIL (took %.3fms to execute)\n\n", (double) (end - start) * 1000 / CLOCKS_PER_SEC);
        return 1;
    }

    printf("4: Calculate new double_complex numbers with basic arithmetic.\n");
    
    printf("    Addition by real: Assert equal 4 + 2i.\n");

    start = clock();
    dcadd_real(z1, 3, result);
    end = clock();

    printf("        %.1f + %.1fi\n", dcreal(result), dcimag(result));
    if(assert_complex_equal(result, 4, 2)){
        printf("        PASS (took %.3fms to execute)\n\n", (double) (end - start) * 1000 / CLOCKS_PER_SEC);
    } else {
        printf("        FAIL (took %.3fms to execute)\n\n", (double) (end - start) * 1000 / CLOCKS_PER_SEC);
        return 1;
    }

    printf("    Addition: Assert equal 6 + 3i.\n");

    start = clock();
    dcadd(z1, z2, result);
    end = clock();

    printf("        %.1f + %.1fi\n", dcreal(result), dcimag(result));
    if(assert_complex_equal(result, 6, 3)){
        printf("        PASS (took %.3fms to execute)\n\n", (double) (end - start) * 1000 / CLOCKS_PER_SEC);
    } else {
        printf("        FAIL (took %.3fms to execute)\n\n", (double) (end - start) * 1000 / CLOCKS_PER_SEC);
        return 1;
    }

    printf("    Subtraction by real: Assert -1 + 2i.\n");

    start = clock();
    dcsub_real(z1, 2, result);
    end = clock();

    printf("        %.1f + %.1fi\n", dcreal(result), dcimag(result));
    if(assert_complex_equal(result, -1, 2)){
        printf("        PASS (took %.3fms to execute)\n\n", (double) (end - start) * 1000 / CLOCKS_PER_SEC);
    } else {
        printf("        FAIL (took %.3fms to execute)\n\n", (double) (end - start) * 1000 / CLOCKS_PER_SEC);
        return 1;
    }

    printf("    Subtraction: Assert equal 4 + -1i.\n");

    start = clock();
    dcsub(z2, z1, result);
    end = clock();

    printf("        %.1f + %.1fi\n", dcreal(result), dcimag(result));
    if(assert_complex_equal(result, 4, -1)){
        printf("        PASS (took %.3fms to execute)\n\n", (double) (end - start) * 1000 / CLOCKS_PER_SEC);
    } else {
        printf("        FAIL (took %.3fms to execute)\n\n", (double) (end - start) * 1000 / CLOCKS_PER_SEC);
        return 1;
    }

    printf("    Multiplication by real: Assert equal 3 + 6i.\n");

    start = clock();
    dcmult_real(z1, 3, result);
    end = clock();

    printf("        %.1f + %.1fi\n", dcreal(result), dcimag(result));
    if(assert_complex_equal(result, 3, 6)){
        printf("        PASS (took %.3fms to execute)\n\n", (double) (end - start) * 1000 / CLOCKS_PER_SEC);
    } else {
        printf("        FAIL (took %.3fms to execute)\n\n", (double) (end - start) * 1000 / CLOCKS_PER_SEC);
        return 1;
    }

    printf("    Multiplication: Assert equal 3 + 11i.\n");

    start = clock();
    dcmult(z1, z2, result);
    end = clock();

    printf("        %.1f + %.1fi\n", dcreal(result), dcimag(result));
    if(assert_complex_equal(result, 3, 11)){
        printf("        PASS (took %.3fms to execute)\n\n", (double) (end - start) * 1000 / CLOCKS_PER_SEC);
    } else {
        printf("        FAIL (took %.3fms to execute)\n\n", (double) (end - start) * 1000 / CLOCKS_PER_SEC);
        return 1;
    }

    printf("    Division by real: Assert equals 0.833 + 1.667i.\n");

    start = clock();
    dcdiv_real(z1, 1.2, result);
    end = clock();

    printf("        %.3f + %.3fi\n", dcreal(result), dcimag(result));
    if(assert_complex_equal(result, 0.833, 1.667)){
        printf("        PASS (took %.3fms to execute)\n\n", (double) (end - start) * 1000 / CLOCKS_PER_SEC);
    } else {
        printf("        FAIL (took %.3fms to execute)\n\n", (double) (end - start) * 1000 / CLOCKS_PER_SEC);
        return 1;
    }

    printf("    Division: Assert equal 0.269 + 0.346i.\n");

    start = clock();
    dcdiv(z1, z2, result);
    end = clock();

    printf("        %.3f + %.3fi\n", dcreal(result), dcimag(result));
    if(assert_complex_equal(result, 0.269, 0.346)){
        printf("        PASS (took %.3fms to execute)\n\n", (double) (end - start) * 1000 / CLOCKS_PER_SEC);
    } else {
        printf("        FAIL (took %.3fms to execute)\n\n", (double) (end - start) * 1000 / CLOCKS_PER_SEC);
        return 1;
    }

    printf("    Exponential: Assert equal -1.131 + 2.472i.\n");

    start = clock();
    dcexp(z1, result);
    end = clock();

    printf("        %.3f + %.3fi\n", dcreal(result), dcimag(result));
    if(assert_complex_equal(result, -1.131, 2.472)){
        printf("        PASS (took %.3fms to execute)\n\n", (double) (end - start) * 1000 / CLOCKS_PER_SEC);
    } else {
        printf("        FAIL (took %.3fms to execute)\n\n", (double) (end - start) * 1000 / CLOCKS_PER_SEC);
        return 1;
    }

    clock_t main_end = clock();
    printf("Test completed in %.3f ms.\n", (double) (main_end - main_start) / CLOCKS_PER_SEC * 1000);

    return 0;
}
