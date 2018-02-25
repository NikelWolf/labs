#include "Boss.h"

using namespace std;

namespace labs_space {
    Boss::Boss(): Human() {
        cout << "number of workers: ";
        cin >> number_of_workers;
    }

    Boss::Boss(string name, string surname, string midname, int age, int number_of_workers): Human(name, surname, midname, age), number_of_workers{number_of_workers} {}

    Boss::~Boss() {}

    void Boss::print() const {
        cout << "name: " << name << "\nsurname: " << surname << "\nmidname: " << midname << "\nage: " << age << "\nnumber of workers: " << number_of_workers << endl;
    }
}
