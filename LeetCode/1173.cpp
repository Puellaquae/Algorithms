#include <iostream>
using namespace std;

class Solution {
public:
    int numPrimeArrangements(int n) {
        auto primeQ = [](int x) {
            if (x < 2) {
                return false;
            }
            for (int i = 2; i < x; i++) {
                if (x % i == 0) {
                    return false;
                }
            }
            return true;
        };
        int primeCnt = 0;
        for (int i = 1; i <= n; i++) {
            if (primeQ(i)) {
                primeCnt++;
            }
        }
        long long res = 1;
        for (int i = 1; i <= primeCnt; i++) {
            res = res * i % 1000000007;
        }
        for (int i = 1; i <= n - primeCnt; i++) {
            res = res * i % 1000000007;
        }
        return res;
    }
};

int main() {
    Solution s;
    cout << s.numPrimeArrangements(5) << endl;
    cout << s.numPrimeArrangements(100) << endl;
}