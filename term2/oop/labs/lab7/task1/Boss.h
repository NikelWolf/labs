#pragma once

#include <iostream>

#include "Human.h"

using namespace std;

namespace labs_space {
    class Boss: public Human {
    private:
        int number_of_workers;
    public:
        Boss();
        Boss(string name, string surname, string midname, int age, int number_of_workers);
        ~Boss();
        void print() const;
    };
}
