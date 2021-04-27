//Adrien and Austin

#include <iostream>
using namespace std;
int main() {
    int n, k;
    cin >> n >> k;
    if (n == 0 || (k == 1 && n % 2 == 0)) {
        cout << "Austin\n";
    } else {
        cout << "Adrien\n";
    }
    return 0;
}