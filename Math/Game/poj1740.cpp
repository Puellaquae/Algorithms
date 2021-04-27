// A New Stone Game

#include <cstring>
#include <iostream>
using namespace std;
#define MAX_N 100
int count[MAX_N + 5];

int main() {
    int n, m, i;
    while (cin >> n && n != 0) {
        memset(count, 0, sizeof count);
        for (i = 0; i < n; i++) {
            cin >> m;
            count[m]++;
        }
        for (i = 1; i <= MAX_N; i++) {
            if (count[i] % 2 == 1) {
                break;
            }
        }
        cout << (i <= MAX_N) << endl;
    }
    return 0;
}