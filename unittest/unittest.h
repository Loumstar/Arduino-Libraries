#ifdef __cplusplus
extern "C" {
#endif

#ifndef UNITTEST_H
    #define UNITTEST_H

    #include <stdbool.h>
    #include <string.h>
    #include <math.h>

    bool assert_int_equal(int a, int b);

    bool assert_double_equal(double a, double b);

    bool assert_double_similar(double a, double b, double max_difference);

#endif

#ifdef __cplusplus
}
#endif
