#pragma once

#include <iostream>
#include <string>
#include <vector>

using namespace std;

namespace labs_space {
class Tiles {
public:
    string brand;
    double size_h, size_w, price;

    Tiles() {
        size_h = size_w = price = 0;
        brand = "";
    }
    Tiles(double price, double size_h, double size_w, string brand) {
        this->brand = brand;
        this->price = price;
        this->size_h = size_h;
        this->size_w = size_w;
    }
    Tiles(string brand = "", double price = 0, double size_h = 0, double size_w = 0) : size_h{size_h}, size_w{size_w}, price{price}, brand{brand} {}
    Tiles(const Tiles &t) {
        brand = t.brand;
        price = t.price;
        size_h = t.size_h;
        size_w = t.size_w;
    }
    ~Tiles() {}

    void get_data() const {
        cout << "brand: " << brand << "\nsize: " << size_w << "x" << size_h << "\nprice: " << price << "\n";
    }
};
} // namespace labs_space
