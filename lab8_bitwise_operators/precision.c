// precision.c
// floating point representations
// returning the immediate next representable float in 
// ascending numerical order towards +Inf

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

float u2f(unsigned int d) {
    union {
        unsigned int u;
        float f;
    } v;
    v.u = d;
    return v.f;
}

/*
 * next_float - Return the immediately following representable float
 *   in ascending order towards +infinity.
 *
 * Use f2u and u2f to access and construct the raw 32-bit representations.
 * Ensure your logic accounts for:
 *   - Special values (+Infinity, NaN)
 *   - Zero (+0.0f and -0.0f)
 *   - Positive vs. negative numbers (sign-magnitude property)
 */
float next_float(float f) {
    // TODO: Implement sign-aware float stepping using f2u and u2f
    unsigned int q = f2u(f);
    // get sign bit
    unsigned int sign = (q >> 31) & 0x1;
    unsigned int exp = (q >> 23) & 0xFF;
    // if the number is non-finite (exponent = 255)
    if (exp == 0xFF) {
        return f;
    }
    // zero values check
    if ((q & 0x7FFFFFFF) == 0) {
        return u2f(0x1);
    }
    // negative sign check
    if (sign == 1) {
        // return negative + 1
        return u2f(f2u(f) -1);
    } 
    // positive sign check
    else if (sign == 0) {
        // return positive + 1
        return u2f(f2u(f) + 1);
    }
    
    
    return 0.0f;
}

int main(void) {
    float f1 = 1.0f;
    float next1 = next_float(f1);
    printf("next_float( 1.0) = %1.23f (diff: %e)\n", next1, next1 - f1);

    float f2 = -1.0f;
    float next2 = next_float(f2);
    printf("next_float(-1.0) = %1.23f (diff: %e)\n", next2, next2 - f2);

    float f3 = 0.0f;
    float next3 = next_float(f3);
    printf("next_float( 0.0) = %e (hex: 0x%08X)\n", next3, f2u(next3));

    float f4 = 7.753e9f;
    float next4 = next_float(f4);
    printf("next_float(7.753e9) = %1.23f (diff: %f)\n", next4, next4 - f4);

    return EXIT_SUCCESS;
}