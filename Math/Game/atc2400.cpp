//Alice & Brown

#include <iostream>
using namespace std;
typedef long long i64;
int main() {
    i64 x, y;
    cin >> x >> y;
    if (-1 <= (x - y) && (x - y) <= 1) {
        cout << "Brown\n";
    } else {
        cout << "Alice\n";
    }
}