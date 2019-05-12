#pragma once

#include <exception>
#include <iostream>

using namespace std;

namespace labs_space {
class Child {
private:
    string name, surname;
    unsigned int age;

public:
    Child();
    Child(istream &in, ostream &out);
    Child(string name, string surname, unsigned int age);
    Child(const Child &c);
    Child(Child &&c);
    ~Child();
    Child &operator=(const Child &c);
    Child &operator=(Child &&c);
    void set_name(string name);
    const string &get_name() const;
    void set_surname(string surname);
    const string &get_surname() const;
    void set_age(unsigned int age);
    unsigned int get_age() const;
    void read_info(istream &in = cin, ostream &out = cout);
    void display() const;
};
} // namespace labs_space
