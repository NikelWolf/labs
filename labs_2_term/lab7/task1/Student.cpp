#include <iostream>

#include "Student.h"

using namespace std;

namespace labs_space {
    Student::Student():Human() {
        cout << "on lesson?[Y/n] ";
        char c;
        cin >> c;
        switch (tolower(c)) {
            case 'y':
                on_lesson = true;
                break;
            case 'n':
            default:
                on_lesson = false;
                break;
        }
    }

    Student::Student(string name, string surname, string midname, int age, bool on_lesson): Human(name, surname, midname, age), on_lesson{on_lesson} {}
    Student::~Student() {}

    void Student::print() const {
        cout << "name: " << name << "\nsurname: " << surname << "\nmidname: " << midname << "\nage: " << age << "\non lesson: " << on_lesson << endl;
    }
}
