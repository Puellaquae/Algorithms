// Nim

#include <iostream>

template <int MAX_N> class NimSolver {
    int a[MAX_N];

public:
    void solve() {
        int n;
        while (std::cin >> n && n != 0) {
            int sum = 0;
            for (int i = 0; i < n; i++) {
                std::cin >> a[i];
                sum ^= a[i];
            }
            int cnt = 0;
            for (int i = 0; i < n; i++) {
                if ((sum ^ a[i]) < a[i]) {
                    cnt++;
                }
            }
            std::cout << cnt << "\n";
        }
    }
};

int main() {
    NimSolver<1010> solver;
    solver.solve();
    return 0;
}