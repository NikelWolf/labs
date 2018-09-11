#include "Complex.h"

namespace labs_space {
    Complex::Complex():
                re{0}, im{0} {}
    Complex::Complex(double r):
                re{r}, im{0} {}
    Complex::Complex(double r, double i):
                re{r}, im{i} {}
    Complex::Complex(const Complex& c):
                re{c.re}, im{c.im} {}
    Complex::Complex(Complex&& c):
                re{c.re}, im{c.im} {}
    Complex::~Complex() {}

    const double& Complex::real() const {
        return re;
    }

    Complex& Complex::real(double re) {
        this->re = re;
        return *this;
    }

    const double& Complex::imag() const {
        return im;
    }

    Complex& Complex::imag(double im) {
        this->im = im;
        return *this;
    }

    Complex& Complex::operator=(const Complex& c) {
        re = c.re;
        im = c.im;
        return *this;
    }

    Complex& Complex::operator=(Complex&& c) {
        re = c.re;
        im = c.im;
        return *this;
    }

    Complex& Complex::operator+=(Complex& c) {
        re += c.re;
        im += c.im;
        return *this;
    }

    Complex& Complex::operator*=(Complex& c) {
        re = re*c.re - im*c.im;
        im = re*c.im + im*c.re;
        return *this;
    }

    Complex& Complex::operator-=(Complex& c) {
        re -= c.re;
        im -= c.im;
        return *this;
    }

    Complex& Complex::operator/=(Complex& c) {
        Complex temp;
        double r = re*c.re + im*c.im;
        temp.real((re*c.re + im*c.im)/r);
        temp.imag((im*c.re - re*c.im)/r);
        re = temp.re;
        im = temp.im;
        return *this;
    }

    double abs(const Complex& c) {
        return sqrt(c.real()*c.real() + c.imag()*c.imag());
    }

    Complex operator+(const Complex& a, const Complex& b) {
        return Complex(a.real() + b.real(), a.imag() + b.imag());
    }

    Complex operator-(const Complex& a, const Complex& b) {
        return Complex(a.real() - b.real(), a.imag() - b.imag());
    }

    Complex operator*(const Complex& a, const Complex& b) {
        return Complex(a.real()*b.real() - a.imag()*b.imag(), a.real()*b.imag() + a.imag()*b.real());
    }

    Complex operator/(const Complex& a, const Complex& b) {
        Complex temp;
        double r = a.real()*b.real() + a.imag()*b.imag();
        temp.real((a.real()*b.real() + a.imag()*b.imag())/r);
        temp.imag((a.imag()*b.real() - a.real()*b.imag())/r);
        return temp;
    }

    bool operator==(const Complex& a, const Complex& b) {
        if (a.real() == b.real() && a.imag() == b.imag()) {
            return true;
        }

        return false;
    }

    bool operator!=(const Complex& a, const Complex& b) {
        return !(a==b);
    }

    bool operator<(const Complex& a, const Complex& b) {
        return abs(a) < abs(b);
    }

    bool operator<=(const Complex& a, const Complex& b) {
        return abs(a) <= abs(b);
    }

    bool operator>(const Complex& a, const Complex& b) {
        return abs(a) > abs(b);
    }

    bool operator>=(const Complex& a, const Complex& b) {
        return abs(a) >= abs(b);
    }

    ostream& operator<<(ostream& out, const Complex& c) {
        out << "(" << c.real() << (c.imag() < 0 ? " - i" : " + i") << abs(c.imag()) << ")";
        return out;
    }

    istream& operator>>(istream& in, Complex& c) {
        string line;
        getline(in, line);
        const char *line_data = line.c_str();

        char c_s;
        double r, i;
        if (sscanf(line_data, "(%lg %c i%lg)", &r, &c_s, &i) != 3 && sscanf(line_data, "%lg %c i%lg", &r, &c_s, &i) != 3) {
            in.setstate(istream::failbit);
            return in;
        }

        i = c_s == '-' ? -i : i;

        c.real(r);
        c.imag(i);

        return in;
    }
}
