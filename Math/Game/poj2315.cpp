// Football Game

#include <cstring>
#include <iostream>
using namespace std;
const int MAX_N = 35;
const int MAX_S = 27;
#define TWO_PI 6.283185307179586476925286766559
int S[MAX_N], XOR[MAX_S];
int N, M, L, R;
int distance(int s) { return (int)(s / (TWO_PI * R)) + 1; }

bool solve() {
    memset(XOR, 0, sizeof(XOR));
    int K = distance(L);
    for (int i = 0; i < N; i++) {
        int g = distance(S[i]) % K;
        for (int j = 0; g; j++, g >>= 1) {
            XOR[j] += g & 1;
        }
    }
    for (int i = 0; i < MAX_S; i++) {
        if (XOR[i] % (M + 1)) {
            return true;
        }
    }
    return false;
}

int main() {
    while (cin >> N >> M >> L >> R) {
        for (int i = 0; i < N; i++) {
            cin >> S[i];
        }
        puts(solve() ? "Alice" : "Bob");
    }
}