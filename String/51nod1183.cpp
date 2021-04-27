// 编辑距离

#include <algorithm>
#include <iostream>
#include <cstring>
using namespace std;
string A, B;
int Levs[1005][1005];
int Lev(int i, int j) {
    if (Levs[i][j] != -1)
        return Levs[i][j];
    if (min(i, j) == 0) {
        Levs[i][j] = max(i, j);
    } else {
        Levs[i][j] = min(min(Lev(i - 1, j) + 1, Lev(i, j - 1) + 1),
                         Lev(i - 1, j - 1) + (A[i - 1] != B[j - 1]));
    }
    return Levs[i][j];
}

int main() {
    memset(Levs, -1, sizeof Levs);
    cin >> A >> B;
    cout << Lev(A.size(), B.size());
}