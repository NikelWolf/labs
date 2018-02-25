#include "praepostor.h"


namespace labs_space {
    praepostor::praepostor(string name, string surname, string group_number, unsigned int count_of_students): student(name, surname, group_number), count_of_students{count_of_students} {}
    praepostor::~praepostor() {}
    unsigned int praepostor::count_of_students_in_group() const {
        return count_of_students;
    }
}
