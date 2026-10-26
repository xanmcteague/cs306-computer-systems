// twice_half.c

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// Define f2u, u2f, float_twice, and float_half above main
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

// float_twice
float float_twice(float f) {
    unsigned int u = f2u(f);
    unsigned int sign = u & 0x80000000u;
    unsigned int mag = u & 0x7FFFFFFFu;
    unsigned int exp = mag >> 23;

    if (exp == 0xFF) return f;
    if (exp == 0) return u2f(sign | (mag << 1));
    if (exp == 0xFE) return u2f(sign | 0x7F800000u);
    return u2f(sign | (mag + 0x00800000u));
}

// float_half
float float_half(float f) {
    unsigned int u = f2u(f);
    unsigned int sign = u & 0x80000000u;
    unsigned int mag = u & 0x7FFFFFFFu;
    unsigned int exp = mag >> 23;

    if (exp == 0xFF) return f;
    if (exp >= 2) return u2f(sign | (mag - 0x00800000u));
    unsigned int r = mag >> 1;
    if ((mag & 1u) && (r & 1u)) r++;
    return u2f(sign | r);
}

int main(void) {
    float val = 1.5f;
    printf("float_twice(%f) = %f\n", val, float_twice(val));
    printf("float_half(%f)  = %f\n", val, float_half(val));
    return EXIT_SUCCESS;
}