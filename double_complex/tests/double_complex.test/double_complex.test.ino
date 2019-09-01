#include <SoftwareSerial.h>

#include "double_complex.h"
#include "unittest.h"

#define PASS_LED 3
#define FAIL_LED 4

char msg[100];

bool assert_complex_equal(const double_complex z, double real, double imag){
    return assert_double_equal(dcreal(z), real) 
        && assert_double_equal(dcimag(z), imag);
}

void setup(void){
    Serial.begin(9600);
    while(!Serial);
}

int main(void){
    uint32_t main_start = micros();
    uint32_t start, end;

    const double_complex z1 = {1, 2}; // 1 + 2i
    const double_complex z2 = {5, 1}; // 5 + i

    double_complex result = {1, -2}; //something non-zero

    double real, imag;

    printf("1: Find the real and imaginary components of a double_complex number.\n");
    
    printf("    Assert equal 1 + 2i.\n");

    start = micros();
    real = dcreal(z1);
    imag =  dcimag(z1);
    end = micros();

    sprintf(msg, "        %.1f + %.1fi\n", real, imag);
    if(assert_double_equal(dcreal(z1), 1) && assert_double_equal(dcimag(z1), 2)){
        sprintf(msg, "        PASS (took %.3fms to execute)\n\n", (double) (end - start) / 1000);
        Serial.print(msg);
    } else {
        sprintf(msg, "        FAIL (took %.3fms to execute)\n\n", (double) (end - start) / 1000);
        Serial.print(msg);
        digitalWrite(FAIL_LED, HIGH);
        while(true);
    }



    printf("2: Set a double_complex number to zero.\n");

    printf("    Assert equal 0 + 0i.\n");

    start = micros();
    dcset_zero(result);
    end = micros();

    sprintf(msg, "        %.1f + %.1fi\n", dcreal(result), dcimag(result));
    if(assert_complex_equal(result, 0, 0)){
        sprintf(msg, "        PASS (took %.3fms to execute)\n\n", (double) (end - start) / 1000);
        Serial.print(msg);
    } else {
        sprintf(msg, "        FAIL (took %.3fms to execute)\n\n", (double) (end - start) / 1000);
        Serial.print(msg);
        digitalWrite(FAIL_LED, HIGH);
        while(true);
    }



    printf("3: Find the modulus of a double_complex number.\n");

    printf("    Conjugate: Assert equal 1 + -2i.\n");

    start = micros();
    dcconj(z1, result);
    end = micros();

    sprintf(msg, "        %.1f + %.1fi\n", dcreal(result), dcimag(result));
    if(assert_double_equal(dcreal(result), 1) && assert_double_equal(dcimag(result), -2)){
        sprintf(msg, "        PASS (took %.3fms to execute)\n\n", (double) (end - start) / 1000);
        Serial.print(msg);
    } else {
        sprintf(msg, "        FAIL (took %.3fms to execute)\n\n", (double) (end - start) / 1000);
        Serial.print(msg);
        digitalWrite(FAIL_LED, HIGH);
        while(true);
    }

    printf("    Modulus: Assert equal the square root of 5 = 2.236...\n");

    start = micros();
    real = dcabs(z1);
    end = micros();

    sprintf(msg, "        %.3f...\n", real);
    if(assert_double_equal(dcabs(z1), 2.236)){
        sprintf(msg, "        PASS (took %.3fms to execute)\n\n", (double) (end - start) / 1000);
        Serial.print(msg);
    } else {
        sprintf(msg, "        FAIL (took %.3fms to execute)\n\n", (double) (end - start) / 1000);
        Serial.print(msg);
        digitalWrite(FAIL_LED, HIGH);
        while(true);
    }

    printf("4: Calculate new double_complex numbers with basic arithmetic.\n");
    
    printf("    Addition by real: Assert equal 4 + 2i.\n");

    start = micros();
    dcadd_real(z1, 3, result);
    end = micros();

    sprintf(msg, "        %.1f + %.1fi\n", dcreal(result), dcimag(result));
    if(assert_complex_equal(result, 4, 2)){
        sprintf(msg, "        PASS (took %.3fms to execute)\n\n", (double) (end - start) / 1000);
        Serial.print(msg);
    } else {
        sprintf(msg, "        FAIL (took %.3fms to execute)\n\n", (double) (end - start) / 1000);
        Serial.print(msg);
        digitalWrite(FAIL_LED, HIGH);
        while(true);
    }

    printf("    Addition: Assert equal 6 + 3i.\n");

    start = micros();
    dcadd(z1, z2, result);
    end = micros();

    sprintf(msg, "        %.1f + %.1fi\n", dcreal(result), dcimag(result));
    if(assert_complex_equal(result, 6, 3)){
        sprintf(msg, "        PASS (took %.3fms to execute)\n\n", (double) (end - start) / 1000);
        Serial.print(msg);
    } else {
        sprintf(msg, "        FAIL (took %.3fms to execute)\n\n", (double) (end - start) / 1000);
        Serial.print(msg);
        digitalWrite(FAIL_LED, HIGH);
        while(true);
    }

    printf("    Subtraction by real: Assert -1 + 2i.\n");

    start = micros();
    dcsub_real(z1, 2, result);
    end = micros();

    sprintf(msg, "        %.1f + %.1fi\n", dcreal(result), dcimag(result));
    if(assert_complex_equal(result, -1, 2)){
        sprintf(msg, "        PASS (took %.3fms to execute)\n\n", (double) (end - start) / 1000);
        Serial.print(msg);
    } else {
        sprintf(msg, "        FAIL (took %.3fms to execute)\n\n", (double) (end - start) / 1000);
        Serial.print(msg);
        digitalWrite(FAIL_LED, HIGH);
        while(true);
    }

    printf("    Subtraction: Assert equal 4 + -1i.\n");

    start = micros();
    dcsub(z2, z1, result);
    end = micros();

    sprintf(msg, "        %.1f + %.1fi\n", dcreal(result), dcimag(result));
    if(assert_complex_equal(result, 4, -1)){
        sprintf(msg, "        PASS (took %.3fms to execute)\n\n", (double) (end - start) / 1000);
        Serial.print(msg);
    } else {
        sprintf(msg, "        FAIL (took %.3fms to execute)\n\n", (double) (end - start) / 1000);
        Serial.print(msg);
        digitalWrite(FAIL_LED, HIGH);
        while(true);
    }

    printf("    Multiplication by real: Assert equal 3 + 6i.\n");

    start = micros();
    dcmult_real(z1, 3, result);
    end = micros();

    sprintf(msg, "        %.1f + %.1fi\n", dcreal(result), dcimag(result));
    if(assert_complex_equal(result, 3, 6)){
        sprintf(msg, "        PASS (took %.3fms to execute)\n\n", (double) (end - start) / 1000);
        Serial.print(msg);
    } else {
        sprintf(msg, "        FAIL (took %.3fms to execute)\n\n", (double) (end - start) / 1000);
        Serial.print(msg);
        digitalWrite(FAIL_LED, HIGH);
        while(true);
    }

    printf("    Multiplication: Assert equal 3 + 11i.\n");

    start = micros();
    dcmult(z1, z2, result);
    end = micros();

    sprintf(msg, "        %.1f + %.1fi\n", dcreal(result), dcimag(result));
    if(assert_complex_equal(result, 3, 11)){
        sprintf(msg, "        PASS (took %.3fms to execute)\n\n", (double) (end - start) / 1000);
        Serial.print(msg);
    } else {
        sprintf(msg, "        FAIL (took %.3fms to execute)\n\n", (double) (end - start) / 1000);
        Serial.print(msg);
        digitalWrite(FAIL_LED, HIGH);
        while(true);
    }

    printf("    Division by real: Assert equals 0.833 + 1.667i.\n");

    start = micros();
    dcdiv_real(z1, 1.2, result);
    end = micros();

    sprintf(msg, "        %.3f + %.3fi\n", dcreal(result), dcimag(result));
    if(assert_complex_equal(result, 0.833, 1.667)){
        sprintf(msg, "        PASS (took %.3fms to execute)\n\n", (double) (end - start) / 1000);
        Serial.print(msg);
    } else {
        sprintf(msg, "        FAIL (took %.3fms to execute)\n\n", (double) (end - start) / 1000);
        Serial.print(msg);
        digitalWrite(FAIL_LED, HIGH);
        while(true);
    }

    printf("    Division: Assert equal 0.269 + 0.346i.\n");

    start = micros();
    dcdiv(z1, z2, result);
    end = micros();

    sprintf(msg, "        %.3f + %.3fi\n", dcreal(result), dcimag(result));
    if(assert_complex_equal(result, 0.269, 0.346)){
        sprintf(msg, "        PASS (took %.3fms to execute)\n\n", (double) (end - start) / 1000);
        Serial.print(msg);
    } else {
        sprintf(msg, "        FAIL (took %.3fms to execute)\n\n", (double) (end - start) / 1000);
        Serial.print(msg);
        digitalWrite(FAIL_LED, HIGH);
        while(true);
    }

    printf("    Exponential: Assert equal -1.131 + 2.472i.\n");

    start = micros();
    dcexp(z1, result);
    end = micros();

    sprintf(msg, "        %.3f + %.3fi\n", dcreal(result), dcimag(result));
    if(assert_complex_equal(result, -1.131, 2.472)){
        sprintf(msg, "        PASS (took %.3fms to execute)\n\n", (double) (end - start) / 1000);
        Serial.print(msg);
    } else {
        sprintf(msg, "        FAIL (took %.3fms to execute)\n\n", (double) (end - start) / 1000);
        Serial.print(msg);
        digitalWrite(FAIL_LED, HIGH);
        while(true);
    }

    uint32_t main_end = micros();
    printf("Test completed in %.3f ms.\n", (double) (main_end - main_start) / 1000);
    
    digitalWrite(PASS_LED, HIGH);
    while(true);
}