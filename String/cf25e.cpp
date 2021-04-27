// Test

#include <algorithm>
#include <cstring>
#include <iostream>

using namespace std;
using ull = unsigned long long;
const int MAX_LENGTH = 100000 + 8;
const ull B = 100000007ULL;

char s[3][MAX_LENGTH];
ull H[3][MAX_LENGTH], B_to[MAX_LENGTH] = {1ULL};
int id[3] = {0, 1, 2}, len[3];

void init_hash() {
    for (int i = 0; i < 3; ++i) {
        for (int j = 1; j < len[i] + 1; ++j) {
            H[i][j] = H[i][j - 1] * B + s[i][j];
        }
    }

    int n = max(max(len[0], len[1]), len[2]);
    for (int i = 1; i < n + 1; ++i) {
        B_to[i] = B_to[i - 1] * B;
    }
}

inline ull hash_of(ull *h, int b, int l) {
    return h[b + l - 1] - h[b - 1] * B_to[l];
}

bool contain(int a, int b) {
    if (len[a] < len[b])
        return false;
    ull bh = H[b][len[b]];
    for (int i = 1; i + len[b] <= len[a]; ++i)
        if (hash_of(H[a], i, len[b]) == bh)
            return true;
    return false;
}

int overlap(int a, int b) {
    int ans = 0;
    for (int i = 1; i <= min(len[a], len[b]); ++i) {
        if (hash_of(H[a], len[a] - i + 1, i) == hash_of(H[b], 1, i))
            ans = i;
    }

    return ans;
}

int solve() {
    int ans = MAX_LENGTH * 3;
    for (int i = 0; i < 2; ++i) {
        for (int j = i + 1; j < 3; ++j) {
            if (contain(i, j) || contain(j, i)) {
                int x = len[i] > len[j] ? i : j;
                int y = 3 - i - j;
                if (contain(x, y) || contain(y, x))
                    return max(len[x], len[y]);
                return len[x] + len[y] - max(overlap(x, y), overlap(y, x));
            }
        }
    }
    do
        ans = min(ans, len[0] + len[1] + len[2] - overlap(id[0], id[1]) -
                           overlap(id[1], id[2]));
    while (next_permutation(id, id + 3));
    return ans;
}

int main() {
    for (int i = 0; i < 3; ++i) {
        gets(s[i] + 1);
        len[i] = strlen(s[i] + 1);
    }
    init_hash();
    printf("%d\n", solve());
    return 0;
}