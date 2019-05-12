#include <algorithm>
#include <iostream>
#include <set>
#include <vector>

using namespace std;

int max_road = 10000;
int city_index;

int main() {
    char cities[3] = {'A', 'B', 'C'};
    int roads_to_a[4] = {0, 0, 0};
    int roads_to_b[4] = {0, 0, 0};
    int roads_to_c[4] = {0, 0, 0};
    int sum_length[3] = {0, 0, 0};

    cout << "There are 3 cities : A,B and C;\n";

    cout << "Enter the length of road[A-B]\n";
    cin >> roads_to_a[1];
    roads_to_b[0] = roads_to_a[1];

    cout << "\nEnter the length of road[A-C]\n";
    cin >> roads_to_a[2];
    roads_to_c[0] = roads_to_a[2];

    cout << "\nEnter the length of road[B-C]\n";
    cin >> roads_to_b[2];
    roads_to_c[1] = roads_to_b[2];

    cout << "\tA\tB\tC\nA:";
    for (int i = 0; i < 3; i++) {
        cout << "\t" << roads_to_a[i];
        sum_length[0] += roads_to_a[i];
    }
    cout << "\t- summary length: " << sum_length[0];
    cout << "\n\n";

    cout << "\nB:";
    for (int i = 0; i < 3; i++) {
        cout << "\t" << roads_to_b[i];
        sum_length[1] += roads_to_b[i];
    }
    cout << "\t- summary length: " << sum_length[1];
    cout << "\n\n";

    cout << "\nC:";
    for (int i = 0; i < 3; i++) {
        cout << "\t" << roads_to_c[i];
        sum_length[2] += roads_to_c[i];
    }
    cout << "\t- summary length: " << sum_length[2];

    for (int i = 0; i < 3; i++) {
        if (max_road > sum_length[i]) {
            max_road = sum_length[i];
            city_index = i;
        }
    }

    cout << "\nThe shortest road summ is " << max_road << " for city " << cities[city_index];
    return 0;
}
