#include <SoftwareSerial.h>

#include "int_complex.h"
#include "unittest.h"

#define PASS_LED 3
#define FAIL_LED 4

char msg[100];

bool assert_int_complex_equal(const int_complex z, int real, int imag){
    return icreal(z) == real && icimag(z) == imag;
}

void setup(void){
    Serial.begin(9600);
    while(!Serial);
}

void loop(void){
    uint32_t main_start = micros();
    uint32_t start, end;

    int_complex z1 = {62, 12};
    int_complex z2 = {76, 93};

    int_complex target_1 = {41, -23};

    int real, imag;
    double dreal;

    Serial.print("1: Find the real and imaginary components of a int_complex number.\n");

    Serial.print("    Assert equal 62 + 12i.\n");

    start = micros();
    real = icreal(z1);
    imag = icimag(z1);
    end = micros();
    
    sprintf("        %d + %di\n", msg, real, imag);
    Serial.print(msg);

    if(assert_int_equal(real, 62) && assert_int_equal(imag, 12)){
        sprintf("        PASS (took %.3fms to execute)\n\n", msg, (double) (end - start) / 1000);
        Serial.print(msg);
    } else {
        sprintf("        FAIL (took %.3fms to execute)\n\n", msg, (double) (end - start) / 1000);
        Serial.print(msg);
        digitalWrite(FAIL_LED, HIGH);
        while(true);
    }



    Serial.print("2: Find the modulus of a int_complex number.\n");

    Serial.print("    Modulus: Assert equal the square root of 3,988 = 63.151...\n");
    
    start = micros();
    dreal = icabs(z1);
    end = micros();

    sprintf("        %.3f...\n", msg, icabs(z1));
    Serial.print(msg);

    if(assert_double_equal(icabs(z1), 63.151)){
        sprintf("        PASS (took %.3fms to execute)\n\n", msg, (double) (end - start) / 1000);
        Serial.print(msg);
    } else {
        sprintf("        FAIL (took %.3fms to execute)\n\n", msg, (double) (end - start) / 1000);
        Serial.print(msg);
        digitalWrite(FAIL_LED, HIGH);
        while(true);
    }



    Serial.print("3: Set the int_complex number to zero and find its conjugate.\n");

    Serial.print("    Set to Zero: Assert equal 0 + 0i.\n");

    start = micros();
    icset_to_zero(target_1);
    end = micros();

    sprintf("        %d + %di\n", msg, icreal(target_1), icimag(target_1));
    Serial.print(msg);

    if(assert_int_equal(icreal(target_1), 0) && assert_int_equal(icimag(target_1), 0)){
        sprintf("        PASS (took %.3fms to execute)\n\n", msg, (double) (end - start) / 1000);
        Serial.print(msg);
    } else {
        sprintf("        FAIL (took %.3fms to execute)\n\n", msg, (double) (end - start) / 1000);
        Serial.print(msg);
        digitalWrite(FAIL_LED, HIGH);
        while(true);
    }

    Serial.print("    Conjugate: Assert equal 62 + -12i.\n");

    start = micros();
    icconj(z1, target_1);
    end = micros();

    sprintf("        %d + %di\n", msg, icreal(target_1), icimag(target_1));
    Serial.print(msg);

    if(assert_int_equal(icreal(target_1), 62) && assert_int_equal(icimag(target_1), -12)){
        sprintf("        PASS (took %.3fms to execute)\n\n", msg, (double) (end - start) / 1000);
        Serial.print(msg);
    } else {
        sprintf("        FAIL (took %.3fms to execute)\n\n", msg, (double) (end - start) / 1000);
        Serial.print(msg);
        digitalWrite(FAIL_LED, HIGH);
        while(true);
    }



    Serial.print("4: Calculate new int_complex numbers with basic arithmetic.\n");

    Serial.print("    Addition by real: Assert equal 65 + 12i.\n");

    start = micros();
    icadd_by_real(z1, 3, target_1);
    end = micros();

    sprintf("        %d + %di\n", msg, icreal(target_1), icimag(target_1));
    Serial.print(msg);

    if(assert_int_complex_equal(target_1, 65, 12)){
        sprintf("        PASS (took %.3fms to execute)\n\n", msg, (double) (end - start) / 1000);
        Serial.print(msg);
    } else {
        sprintf("        FAIL (took %.3fms to execute)\n\n", msg, (double) (end - start) / 1000);
        Serial.print(msg);
        digitalWrite(FAIL_LED, HIGH);
        while(true);
    }

    Serial.print("    Addition: Assert equal 138 + 105i.\n");

    start = micros();
    icadd(z1, z2, target_1);
    end = micros();

    sprintf("        %d + %di\n", msg, icreal(target_1), icimag(target_1));
    Serial.print(msg);

    if(assert_int_complex_equal(target_1, 138, 105)){
        sprintf("        PASS (took %.3fms to execute)\n\n", msg, (double) (end - start) / 1000);
        Serial.print(msg);
    } else {
        sprintf("        FAIL (took %.3fms to execute)\n\n", msg, (double) (end - start) / 1000);
        Serial.print(msg);
        digitalWrite(FAIL_LED, HIGH);
        while(true);
    }

    Serial.print("    Subtraction by real: Assert 60 + 12i.\n");

    start = micros();
    icsub_by_real(z1, 2, target_1);
    end = micros();
    
    sprintf("        %d + %di\n", msg, icreal(target_1), icimag(target_1));
    Serial.print(msg);

    if(assert_int_complex_equal(target_1, 60, 12)){
        sprintf("        PASS (took %.3fms to execute)\n\n", msg, (double) (end - start) / 1000);
        Serial.print(msg);
    } else {
        sprintf("        FAIL (took %.3fms to execute)\n\n", msg, (double) (end - start) / 1000);
        Serial.print(msg);
        digitalWrite(FAIL_LED, HIGH);
        while(true);
    }

    Serial.print("    Subtraction: Assert equal 14 + 81i.\n");

    start = micros();
    icsub(z2, z1, target_1);
    end = micros();
    
    sprintf("        %d + %di\n", msg, icreal(target_1), icimag(target_1));
    Serial.print(msg);

    if(assert_int_complex_equal(target_1, 14, 81)){
        sprintf("        PASS (took %.3fms to execute)\n\n", msg, (double) (end - start) / 1000);
        Serial.print(msg);
    } else {
        sprintf("        FAIL (took %.3fms to execute)\n\n", msg, (double) (end - start) / 1000);
        Serial.print(msg);
        digitalWrite(FAIL_LED, HIGH);
        while(true);
    }

    Serial.print("    Division by real: Assert equals 31 + 6i.\n");

    start = micros();
    icdiv_by_real(z1, 2, target_1);
    end = micros();

    sprintf("        %d + %di\n", msg, icreal(target_1), icimag(target_1));
    Serial.print(msg);

    if(assert_int_complex_equal(target_1, 31, 6)){
        sprintf("        PASS (took %.3fms to execute)\n\n", msg, (double) (end - start) / 1000);
        Serial.print(msg);
    } else {
        sprintf("        FAIL (took %.3fms to execute)\n\n", msg, (double) (end - start) / 1000);
        Serial.print(msg);
        digitalWrite(FAIL_LED, HIGH);
        while(true);
    }

    uint32_t main_end = micros();
    printf("Test completed in %.3f ms.\n", (double) (main_end - main_start) / 1000);

    digitalWrite(PASS_LED, HIGH);
    while(true);
}