#include "Child.h"

namespace labs_space {
    Child::Child() {
        read_info();
    }

    Child::Child(istream& in, ostream& out) {
        read_info(in, out);
    }


    Child::Child(string name, string surname, unsigned int age):
                name{name}, surname{surname}, age{age} {}

    Child::Child(const Child& c) {
        name = c.name;
        surname = c.surname;
        age = c.age;
    }

    Child::Child(Child&& c):
                name{c.name}, surname{c.surname}, age{c.age} {
        c.name.clear();
        c.surname.clear();
    }

    Child::~Child() {}

    Child& Child::operator=(Child&& c) {
        name = c.name;
        surname = c.surname;
        age = c.age;
        c.name.clear();
        c.surname.clear();
        return *this;
    }

    Child& Child::operator=(const Child& c) {
        name = c.name;
        surname = c.surname;
        age = c.age;
        return *this;
    }

    void Child::set_name(string name) {
        this->name = name;
    }

    void Child::set_surname(string surname) {
        this->surname = surname;
    }

    void Child::set_age(unsigned int age) {
        this->age = age;
    }

    const string& Child::get_name() const {
        return name;
    }

    const string& Child::get_surname() const {
        return surname;
    }

    unsigned int Child::get_age() const {
        return age;
    }

    void Child::read_info(istream& in = cin, ostream& out = cout) {
        string _name, _surname;
        unsigned int _age;

        out << "name: ";
        if (!(in >> _name)) {
            throw runtime_error{"name reading"};
        }

        out << "surname: ";
        if (!(in >> _surname)) {
            throw runtime_error{"surname reading"};
        }

        out << "age: ";
        if (!(in >> _age)) {
            throw runtime_error{"age reading"};
        }

        this->name = _name;
        this->surname = _surname;
        this->age = _age;
    }

    void Child::display() const {
        cout << "[Child(" << this << "): {name=" << name << ", surname=" << surname << ", age=" << age << "}]\n";
    }
}
