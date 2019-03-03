#include "Complex.h"

Complex complex_add(Complex a, Complex b) {
    return (Complex) {a.re + b.re, a.im + b.im};
}

Complex complex_substract(Complex a, Complex b) {
    return (Complex) {a.re - b.re, a.im - b.im};
}

Complex complex_multiply(Complex a, Complex b) {
    return (Complex) {a.re*b.re - a.im*b.im, a.re*b.im - a.im*b.re};
}

Complex complex_division(Complex a, Complex b) {
    return (Complex) {(a.re*b.re + a.im*b.im)/(b.re * b.re + b.im * b.im), (a.im*b.re + a.re*b.im)/(b.re * b.re + b.im * b.im)};
}
