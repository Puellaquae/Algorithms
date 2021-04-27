#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
using i32 = int32_t;
using u32 = uint32_t;

const i32 MAX_N = 100000;
i32 MinFactor[MAX_N + 1];
vector<i32> Bucket[MAX_N + 1];

void InitPrimes() {
    vector<i32> Primes;
    for (i32 i = 2; i <= MAX_N; i++) {
        if (MinFactor[i] == 0) {
            Primes.push_back(i);
            MinFactor[i] = i;
        }
        for (auto P : Primes) {
            if (MAX_N < i * P) {
                break;
            }
            MinFactor[i * P] = P;
            if (i % P == 0) {
                break;
            }
        }
        Bucket[MinFactor[i]].push_back(i);
    }
}

void Solve() {
    i32 N;
    cin >> N;
    vector<i32> Ans;
    vector<i32> Borrow;
    for (i32 PrimeMaybe = N + 1; PrimeMaybe-- > 3;) {
        auto &A = Bucket[PrimeMaybe];
        if (A.empty()) {
            continue;
        }
        const auto M = upper_bound(A.begin(), A.end(), N) - A.begin();
        if (M % 2 == 0) {
            Ans.insert(Ans.end(), Bucket[PrimeMaybe].begin(), Bucket[PrimeMaybe].begin() + M);
        } else {
            if (2 * PrimeMaybe <= N) {
                Borrow.push_back(2 * PrimeMaybe);
                Ans.push_back(PrimeMaybe);
                Ans.push_back(2 * PrimeMaybe);
            }
            Ans.insert(Ans.end(), ++Bucket[PrimeMaybe].begin(), Bucket[PrimeMaybe].begin() + M);
        }
    }
    if (2 <= N) {
        auto &A = Bucket[2];
        const auto M = upper_bound(A.begin(), A.end(), N) - A.begin();
        reverse(Borrow.begin(), Borrow.end());
        i32 i = 0;
        for (auto X : Borrow) {
            while (i < M && A[i] != X) {
                Ans.push_back(A[i++]);
            }
            i++;
        }
        while (i < M) {
            Ans.push_back(A[i++]);
        }
        if (Ans.size() % 2 == 1) {
            Ans.pop_back();
        }
    }
    cout << Ans.size() / 2 << " ";
    for (auto An : Ans) {
        cout << An << " ";
    }
    cout << "\n";
}

int main() {
    InitPrimes();
    i32 T;
    cin >> T;
    while (T--) {
        Solve();
    }
}