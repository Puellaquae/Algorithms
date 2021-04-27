#include <algorithm>
#include <iostream>
#include <cstdio>
using namespace std;

int main() {
    double height, up, down, factor;
    while (cin >> height && height != 0.0) {
        cin >> up >> down >> factor;
        double place = 0.0;
        const double delta = up * factor * 0.01;
        for (int day = 1;; day++) {
            place += max(0.0, up);
            if (place > height) {
                printf("success on day %d\n", day);
                break;
            }
            place -= down;
            if (place < 0) {
                printf("failure on day %d\n", day);
                break;
            }
            up -= delta;
        }
    }
    return 0;
}