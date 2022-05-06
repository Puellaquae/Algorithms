#include <cmath>
#include <cstdio>
#include <iostream>
using namespace std;

int main() {
    int x, y;
    cin >> x >> y;
    double r = sqrt(x * x + y * y);
    printf("%.12f %.12f\n", x / r, y / r);
    return 0;
}