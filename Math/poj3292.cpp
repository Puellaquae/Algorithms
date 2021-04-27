// Semi-prime H-numbers

#include <iostream>
#include <vector>
using namespace std;
const int MAX_H = 1000001 + 5;
int HSPrime[MAX_H];
vector<bool> Prime(MAX_H, true);

int main() {
    for (int i = 5; i < MAX_H; i += 4) {
        if (Prime[i] == false)
            continue;
        for (int k = 5; 1LL * i * k < MAX_H; k += 4) {
            Prime[i * k] = false;
        }
    }
    for (int i = 5; i < MAX_H; i += 4) {
        if (!Prime[i])
            continue;
        for (int j = i; 1LL * i * j < MAX_H; j += 4) {
            if (!Prime[j])
                continue;
            HSPrime[i * j] = 1;
        }
    }
    for (int i = 1; i < MAX_H; i++) {
        HSPrime[i] += HSPrime[i - 1];
    }
    ios::sync_with_stdio(false);
    cout.tie(NULL);
    cin.tie(NULL);
    int h;
    while (cin >> h && h) {
        cout << h << " " << HSPrime[h] << '\n';
    }
}
