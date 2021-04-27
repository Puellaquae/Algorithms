// Dead Fraction

#include <iostream>
#include <string>

template <class T> T GCD(T a, T b) {
    if (b == 0) {
        return a;
    } else {
        return GCD(b, a % b);
    }
}
typedef long long int64;

int64 pow10(int64 a) {
    int64 x = 1;
    for (int i = 0; i < a; i++)
        x *= 10;
    return x;
}

using namespace std;
int main() {
    string xx;
    while (cin >> xx && xx != "0") {
        int i = 0;
        for (; i < (int)xx.size() && xx[i] != '.'; i++)
            ;
        int64 a = 0, l = 0;
        for (i++; i < (int)xx.size() && xx[i] != '.'; i++) {
            a = a * 10 + xx[i] - '0';
            l++;
        }
        if (a == 0) {
            cout << "0/1\n";
            continue;
        }
        int64 minx = 0x7fffffffffffffff;
        int64 miny = 0;
        for (int j = 1; j <= l; j++) {
            int64 x = pow10(l) - pow10(l - j);
            int64 y = a - a / pow10(j);
            int64 d = GCD(x, y);
            x /= d;
            y /= d;
            if (minx > x) {
                minx = x;
                miny = y;
            }
        }
        cout << miny << '/' << minx << endl;
    }
}