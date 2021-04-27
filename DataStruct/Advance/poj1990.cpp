// MooFest
//耳背程度v，坐标x
//{forall i where v[i]<v[j]} sum(v[j]*|x[i]-x[j]|)

#include <algorithm>
#include <iostream>
using namespace std;
#define MAX_N 20000 + 16
typedef long long i64;

pair<int, int> cow[MAX_N];
int N;
i64 tCount[MAX_N], tDistance[MAX_N];

// a[0，i]
i64 sum(i64 *bit, int i) {
    i64 s = 0;
    while (i > 0) {
        s += bit[i];
        i -= i & -i;
    }

    return s;
}

// a[from, to)
i64 sum(i64 *bit, int from, int to) {
    return sum(bit, to - 1) - sum(bit, from - 1);
}

// a[i] += x
void add(i64 *bit, int i, i64 x) {
    while (i <= MAX_N) {
        bit[i] += x;
        i += i & -i;
    }
}

int main() {
    cin >> N;
    for (int i = 0; i < N; ++i) {
        cin >> cow[i].first >> cow[i].second;
    }

    sort(cow, cow + N);
    i64 result = 0;
    for (int i = 0; i < N; ++i) {
        int v = cow[i].first, x = cow[i].second;
        i64 left = sum(tCount, 1, x), right = sum(tCount, x + 1, MAX_N);
        result += v * ((left * x - sum(tDistance, 1, x)) +
                       (sum(tDistance, x + 1, MAX_N) - right * x));
        add(tCount, cow[i].second, 1);
        add(tDistance, cow[i].second, cow[i].second);
    }
    cout << result << endl;
    return 0;
}