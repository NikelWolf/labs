#pragma once

#include <cmath>
#include <iostream>
#include <typeinfo>
#include <vector>

using namespace std;

namespace labs_space {
using vector_size_type = long unsigned int;

template <typename T>
class Vector {
private:
    T *elements;
    vector_size_type el_size;
    vector<T> tmp_vector;

    template <typename... TArgs>
    void fill_variance_vector(T head, TArgs... tail) {
        tmp_vector.push_back(head);

        fill_variance_vector(tail...);
    }

public:
    Vector() = delete;

    explicit Vector(vector_size_type size = 10) : tmp_vector{} {
        if (size == 0) {
            throw length_error{"length must be more than 0"};
        }
        elements = new T[size];
        el_size = size;
    }

    explicit Vector(int size = 10) : tmp_vector{} {
        if (size == 0) {
            throw length_error{"length must be more than 0"};
        }
        elements = new T[size];
        el_size = size;
    }

    explicit Vector(long size = 10) : tmp_vector{} {
        if (size == 0) {
            throw length_error{"length must be more than 0"};
        }
        elements = new T[size];
        el_size = size;
    }

    Vector(initializer_list<T> lst) : elements{new T[lst.size()]}, el_size{lst.size()}, tmp_vector{} {
        copy(lst.begin(), lst.end(), elements);
    }

    template <typename... TArgs>
    Vector(T head, TArgs... tail) : tmp_vector{} {
        fill_variance_vector(head, tail...);

        elements = new T[tmp_vector.size()];
        el_size = tmp_vector.size();

        copy(tmp_vector.begin(), tmp_vector.end(), elements);

        tmp_vector.clear();
    }

    Vector(const Vector<T> &v) : elements{new T[v.size()]}, el_size{v.size()} {
        copy(v.begin(), v.end(), elements);
    }

    Vector(Vector<T> &&v) : elements{v.elements}, el_size{v.size()} {
        v.elements = nullptr;
        v.el_size = 0;
    }

    ~Vector() {
        delete[] elements;
    }

    Vector &operator=(const Vector<T> &v) {
        delete[] elements;

        elements = new T[v.size()];
        el_size = v.size();

        for (vector_size_type i = 0; i < size(); i++) {
            elements[i] = v[i];
        }

        return *this;
    }

    Vector &operator=(Vector &&v) {
        elements = v.elements;
        el_size = v.size();

        v.elements = nullptr;
        v.size() = 0;

        return *this;
    }

    T &operator[](vector_size_type i) {
        if (i < 0 || i >= el_size) {
            throw range_error{"out of range"};
        }

        return elements[i];
    }

    const T &operator[](vector_size_type i) const {
        if (i < 0 || i >= el_size) {
            throw range_error{"out of range"};
        }

        return elements[i];
    }

    T *begin() {
        return size() == 0 ? nullptr : &elements[0];
    }

    T *end() {
        return begin() + size();
    }

    const vector_size_type &size() const {
        return el_size;
    }
};

template <typename T>
Vector<T> operator+(const Vector<T> &a, const Vector<T> &b) {
    if (a.size() != b.size()) {
        throw length_error{"vectors must have equal sizes"};
    }

    Vector<T> c{a.size() + b.size()};
    for (vector_size_type i = 0; i < c.size(); i++) {
        c[i] = a[i] + b[i];
    }
    return c;
}

template <typename T>
Vector<T> operator-(const Vector<T> &a, const Vector<T> &b) {
    if (a.size() != b.size()) {
        throw length_error{"vectors must have equal sizes"};
    }

    Vector<T> c{a.size() + b.size()};
    for (vector_size_type i = 0; i < c.size(); i++) {
        c[i] = a[i] - b[i];
    }
    return c;
}

template <typename T, typename Coef_Type>
Vector<T> operator*(Coef_Type rt, const Vector<T> &v) {
    Vector<T> c{v.size()};
    for (vector_size_type i = 0; i < c.size(); i++) {
        c[i] = rt * v[i];
    }
    return c;
}

template <typename T, typename Result_Type>
Result_Type operator*(const Vector<T> &a, const Vector<T> &b) {
    if (a.size() != b.size()) {
        throw length_error{"vectors must have equal sizes"};
    }

    Result_Type result{};
    for (vector_size_type i = 0; i < a.size(); i++) {
        result += a[i] * b[i];
    }
}

template <typename T>
bool operator==(const Vector<T> &a, const Vector<T> &b) {
    if (a.size() != b.size()) {
        throw length_error{"vectors must have equal sizes"};
    }

    for (int i = 0; i < a.size(); i++) {
        if (a[i] != b[i]) {
            return false;
        }
    }

    return true;
}

template <typename T>
bool operator!=(const Vector<T> &a, const Vector<T> &b) {
    return !(a == b);
}

template <typename T>
ostream &operator<<(ostream &out, const Vector<T> &v) {
    out << "[Vector(size: " << v.size() << "; elements type: " << typeid(v[0]).name() << "): {";
    for (vector_size_type i = 0; i < v.size(); i++) {
        out << i << ": " << v[i] << (i == v.size() - 1 ? "}\n" : ", ");
    }
    return out;
}

template <typename T>
istream &operator>>(istream &in, Vector<T> &v) {
    for (vector_size_type i = 0; i < v.size(); i++) {
        if (!(in >> v[i])) {
            in.setstate(istream::failbit);
            return in;
        }
    }
    return in;
}

template <typename T>
T *begin(Vector<T> &v) {
    return v.size() == 0 ? nullptr : &v[0];
}

template <typename T>
T *end(Vector<T> &v) {
    return begin(v) + v.size();
}

template <typename T>
long double abs(const Vector<T> &v) {
    return sqrt(v * v);
}
} // namespace labs_space
