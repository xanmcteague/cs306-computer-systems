// sum.c
// floating-point accumulation 
// and relative ULP comparison

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

unsigned int f2u(float f) {
    union {
        unsigned int u;
        float f;
    } v;
    v.f = f;
    return v.u;
}

/*
 * is_near - Return 1 if the distance between a and b in ULPs is <= max_ulps,
 *   and 0 otherwise.
 *
 * Requirements:
 *   - If a and b are equal (including +0.0f == -0.0f), distance is 0 ULPs.
 *   - If a and b have the same sign, distance in ULPs is the absolute difference
 *     between their integer representations (f2u).
 *   - If signs differ, distance is the sum of their individual distances to zero
 *     (masking off the sign bit).
 */
int is_near(float a, float b, int max_ulps) {
    // TODO: Implement relative ULP comparison
    // max_ulp < 0 guard
    if (max_ulps < 0) {
        return 0;
    }
    
    // ulp_diff
    unsigned int ia = f2u(a), ib = f2u(b);
    unsigned int ulp_diff = (ia > ib) ? ia - ib : ib - ia;
    // zero value case
    if (((f2u(a) & 0x7FFFFFFF) == 0) && ((f2u(b) & 0x7FFFFFFF) == 0)) {
        return 1;
    }
    
    unsigned int sign_a = (f2u(a) >> 31) & 0x1;
    unsigned int sign_b = (f2u(b) >> 31) & 0x1;
    // if signs differ
    if (sign_a != sign_b) {
        // distance = sum of individual distances to zero
        unsigned int masked_a = f2u(a) & 0x7FFFFFFF;
        unsigned int masked_b = f2u(b) & 0x7FFFFFFF;
        unsigned int diff_sum = (masked_a - 0) + (masked_b - 0);
        // if difference <= max
        if (diff_sum <= max_ulps) {
            return 1;
        }
    }
    
    // if ulp_diff < max
    if (ulp_diff <= max_ulps) {
        return 1;
    }
    return 0;
}

int main(void) {
    float a = 0.1f;
    float sum = 0.0f;
    for (int i = 0; i < 1000; i++) {
        sum += a;
    }

    printf("a = %1.23f, sum = %1.23f\n", a, sum);
    printf("sum == 100 ==> %s\n", (sum == 100.0f) ? "TRUE" : "FALSE");

    printf("is_near(sum, 100, 150) ==> %s\n",
           is_near(sum, 100.0f, 150) ? "TRUE" : "FALSE");
    printf("is_near(sum, 100, 100) ==> %s\n",
           is_near(sum, 100.0f, 100) ? "TRUE" : "FALSE");

    return EXIT_SUCCESS;
}