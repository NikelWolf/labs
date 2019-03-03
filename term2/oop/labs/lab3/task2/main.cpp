#include "Tiles.h"

using namespace labs_space;

void fill_tiles(Tiles &t) {
    cout << "brand: ";
    if (!(cin >> t.brand)) {
        throw runtime_error{"brand reading"};
    }

    cout << "size => height width): ";
    if (!(cin >> t.size_h >> t.size_w)) {
        throw runtime_error{"size reading"};
    }

    cout << "price: ";
    if (!(cin >> t.price)) {
        throw runtime_error{"price reading"};
    }
}

int main() {
    Tiles t1, t2;

    fill_tiles(t1);
    fill_tiles(t2);

    t1.get_data();
    t2.get_data();

    return 0;
}
