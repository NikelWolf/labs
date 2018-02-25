#pragma once

#include <string>
#include <vector>
#include <iostream>

using namespace std;

namespace labs_space {
    class Tiles {
    public:
        string brand;
        double size_h, size_w, price;

        ~Tiles() {}

        void get_data() const {
            cout << "brand: " << brand << "\nsize: " << size_w << "x" << size_h << "\nprice: " << price << "\n";
        }
    };
}
