// Sort it

#include <iostream>
using namespace std;
const int MAX_N = 1005;
int Array[MAX_N];
int main() {
    int n;
    while (cin >> n) {
        int sum = 0;
        for (int i = 0; i < n; i++) {
            cin >> Array[i];
        }
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if (Array[i] > Array[j]) {
                    swap(Array[i], Array[j]);
                    sum++;
                }
            }
        }
        cout << sum << endl;
    }
}