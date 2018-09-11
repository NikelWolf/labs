#pragma once

#include <iostream>

using namespace std;

namespace labs_space {
    class Human {
    protected:
        string name;
        string surname;
        string midname;
        int age;
    public:
        Human();
        Human(string name, string surname, string midname, int age);
        virtual ~Human();
        virtual void print() = 0;
    };
}
