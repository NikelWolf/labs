#include <string>

#include "student.h"

using namespace std;

namespace labs_space {
    class praepostor: public student {
    private:
        unsigned int count_of_students;
    public:
        praepostor(string name, string surname, string group_number, unsigned int count_of_students);
        ~praepostor();
        unsigned int count_of_students_in_group() const;
    };
}
