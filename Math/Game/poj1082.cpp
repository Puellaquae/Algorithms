// A Calendar Game

#include <iostream>
using namespace std;
int main() {
    int n, y, m, d;
    cin >> n;
    while (n--) {
        cin >> y >> m >> d;
        if ((m + d) % 2 == 0 || (d == 30 && (m == 9 || m == 11))) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }
}