#include <iostream>

#include "Human.h"

using namespace std;

namespace labs_space {
    Human::Human() {
        cout << "name: ";
        cin >> name;
        cout << "surname: ";
        cin >> surname;
        cout << "midname: ";
        cin >> midname;
        cout << "age: ";
        cin >> age;
    }

    Human::Human(string name, string surname, string midname, int age): name{name}, surname{surname}, midname{midname}, age{age} {}

    Human::~Human() {}
}
