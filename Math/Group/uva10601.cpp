// Cubes

#include <algorithm>
#include <iostream>
#include <iterator>
using namespace std;
typedef long long i64;
const int NUM_SIZE = 12;
const int MAX_N = 15;
const int EDGE_NUM = 6;
const int CYCLIC_NUM = 6;

const int POINT_GROUP = 4;
const int EDGE_GROUP = 6;
const int PLANE_GROUP = 3;
const int CUBE_GROUP = 1;

const int NO_ROTATE = 1;
const int NO_ROTATE_ORDER = 1;

const int ROTATE_120DEG_160DEG = 2;
const int ROTATE_120DEG_160DEG_ORDER = 3;

const int ROTATE_90DEG_270DEG = 2;
const int ROTATE_90DEG_270DEG_ORDER = 4;

const int ROTATE_180DEG = 1;
const int ROTATE_180DEG_ORDER = 2;

const int CYCLIC_COUNT = CUBE_GROUP * NO_ROTATE + PLANE_GROUP * ROTATE_90DEG_270DEG +
        PLANE_GROUP * ROTATE_180DEG + POINT_GROUP * ROTATE_120DEG_160DEG +
        EDGE_GROUP * ROTATE_180DEG;

i64 Combine[MAX_N][MAX_N], A[MAX_N], B[MAX_N];

void Init() {
    for (int i = 0; i <= NUM_SIZE; i++) {
        Combine[i][0] = Combine[i][i] = 1;
        for (int j = 1; j <= i; j++) {
            Combine[i][j] = Combine[i - 1][j] + Combine[i - 1][j - 1];
        }
    }
}

i64 Solve(const int order) {
    i64 n = 0, sum = 1;
    for (int i = 0; i < CYCLIC_NUM; i++) {
        if (B[i] % order)
            return 0;
        B[i] /= order;
        n += B[i];
    }
    for (int i = 0; i < CYCLIC_NUM; i++) {
        sum *= Combine[n][B[i]];
        n -= B[i];
    }
    return sum;
}

i64 Polya() {
    i64 ans = 0;
    copy(begin(A), end(A), B);
    ans += CUBE_GROUP * NO_ROTATE * Solve(NO_ROTATE_ORDER);
    copy(begin(A), end(A), B);
    ans += PLANE_GROUP * ROTATE_90DEG_270DEG * Solve(ROTATE_90DEG_270DEG_ORDER);
    copy(begin(A), end(A), B);
    ans += PLANE_GROUP * ROTATE_180DEG * Solve(ROTATE_180DEG_ORDER);
    copy(begin(A), end(A), B);
    ans += POINT_GROUP * ROTATE_120DEG_160DEG * Solve(ROTATE_120DEG_160DEG_ORDER);

    for (int i = 0; i < EDGE_NUM; i++) {
        for (int j = 0; j < EDGE_NUM; j++) {
            copy(begin(A), end(A), B);
            B[i]--;
            B[j]--;
            if (B[i] < 0 || B[j] < 0)
                continue;

            ans += EDGE_GROUP * ROTATE_180DEG * Solve(ROTATE_180DEG_ORDER);
        }
    }
    return ans / CYCLIC_COUNT;
}

int main() {
    int t;
    cin >> t;
    Init();
    while (t--) {
        fill(begin(A), end(A), 0);
        for (int i = 0, n; i < NUM_SIZE; i++) {
            cin >> n;
            A[n - 1]++;
        }
        cout << Polya() << endl;
    }
}