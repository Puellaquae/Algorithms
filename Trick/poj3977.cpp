// Subset
#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
using namespace std;
typedef long long int64;
typedef map<int64, int>::iterator Iterator;
const int MAX_N = 36;
int64 number[MAX_N];
int64 Abs(const int64 &x) { return x >= 0 ? x : -x; }
int main() {
    int N;
    while (cin >> N && N) {
        for (int i = 0; i < N; ++i) {
            cin >> number[i];
        }
        map<int64, int> Sum2NumCount;
        pair<int64, int> Optimum(Abs(number[0]), 1);
        for (int i = 0; i < (1 << (N / 2)); i++) {
            int64 Sum = 0;
            int NumCount = 0;
            for (int j = 0; j < N / 2; ++j) {
                if ((i >> j) & 1) {
                    Sum += number[j];
                    NumCount++;
                }
            }
            if (NumCount == 0) {
                continue;
            }
            Optimum = min(Optimum, make_pair(Abs(Sum), NumCount));
            Iterator it = Sum2NumCount.find(Sum);
            if (it != Sum2NumCount.end()) {
                it->second = min(it->second, NumCount);
            } else {
                Sum2NumCount[Sum] = NumCount;
            }
        }
        for (int i = 0; i < 1 << (N - N / 2); ++i) {
            int64 Sum = 0;
            int NumCount = 0;
            for (int j = 0; j < N - N / 2; ++j) {
                if ((i >> j) & 1) {
                    Sum += number[N / 2 + j];
                    NumCount++;
                }
            }
            if (NumCount == 0) {
                continue;
            }
            Optimum = min(Optimum, make_pair(Abs(Sum), NumCount));
            Iterator it = Sum2NumCount.lower_bound(-Sum);
            if (it != Sum2NumCount.end()) {
                Optimum = min(Optimum, make_pair(Abs(Sum + it->first), NumCount + it->second));
            }
            if (it != Sum2NumCount.begin()) {
                it--;
                Optimum = min(Optimum, make_pair(Abs(Sum + it->first), NumCount + it->second));
            }
        }
        cout << Abs(Optimum.first) << ' ' << Optimum.second << endl;
    }
    return 0;
}