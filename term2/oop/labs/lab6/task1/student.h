#include <string>

using namespace std;

namespace labs_space {
    class student {
    protected:
        string name;
        string surname;
        string group_number;
    public:
        student() = delete;
        student(string name, string surname, string group_number);
        virtual ~student();
    };
}
