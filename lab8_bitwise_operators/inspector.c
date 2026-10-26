// inspector.c
// extracting sign bit, exponent, and fraction from float and double values of floating point numbers



#include <stdio.h>
#include <stdlib.h>

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

unsigned long long d2u(double f) {
    union {
        unsigned long long u;
        double f;
    } v;
    v.f = f;
    return v.u;
}

double u2d(unsigned long long d) {
    union {
        unsigned long long u;
        double f;
    } v;
    v.u = d;
    return v.f;
}

void inspect_float(float f) {
    unsigned int q = f2u(f);
    // TODO: replace the zeros in the next three lines
    // with the appropriate values extracted from q using bit shifting and masking
    int sign = q >> 31;
    sign = sign & 0x1;
    int exp = q >> 23;
    int mask = 0x000000FF;
    exp = exp & mask;
    
    int frac = q >> 0;
    int exp_mask = 0x007FFFFF;
    frac = frac & exp_mask;

    // Do not change the printf format!
    printf("Inspecting single % e, sign = %d, biased exponent = 0x%x, fraction = 0x%06x\n",
           f, sign, exp, frac);
}

void inspect_double(double f) {
    unsigned long long q = d2u(f);
    // TODO: replace the zeros in the next three lines
    // with the appropriate values extracted from q using bit shifting and masking
    int sign = (int)((q >> 63) & 0x1ULL);                  // 1 sign bit
    unsigned int exp = (unsigned int)((q >> 52) & 0x7FFULL); // 11 exponent bits
    unsigned long long frac = q & 0xFFFFFFFFFFFFFULL;      // 52 fraction bits

    // Do not change the printf format!
    printf("Inspecting double % le, sign = %d, biased exponent = 0x%x, fraction = 0x%013llx\n",
           f, sign, exp, frac);
}

int main(void) {
    printf("0.5 (single) = %f\n", 0.5f);
    inspect_float(0.5f);
    printf("0.5 (double) = %lf\n", 0.5);
    inspect_double(0.5);
    return EXIT_SUCCESS;
}