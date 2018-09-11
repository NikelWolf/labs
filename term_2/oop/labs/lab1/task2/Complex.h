#ifndef COMPLEX_H
#define COMPLEX_H

typedef struct Complex_s {
    double re;
    double im;
} Complex;

Complex complex_add(Complex a, Complex b);
Complex complex_substract(Complex a, Complex b);
Complex complex_multiply(Complex a, Complex b);
Complex complex_division(Complex a, Complex b);
double complex_abs(Complex c);
#endif // !COMPLEX_H
