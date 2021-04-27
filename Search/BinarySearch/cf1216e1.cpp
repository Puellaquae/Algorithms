#include <iostream>
using namespace std;
typedef long long int64;

int main() {
    int q;
    cin >> q;
    while (q--) {
        int64 k;
        cin >> k;
        k--;//first 1
        int64 LengthOfCurrentBlock = 0;
        int64 NextLongerBlockPos = 1;
        int BlockLengthStep = 0;
        for (int64 i = 1;; i++) {
            if (i == NextLongerBlockPos) {
                BlockLengthStep++;
                NextLongerBlockPos *= 10;
            }
            LengthOfCurrentBlock += BlockLengthStep;
            if (k >= LengthOfCurrentBlock) {
                k -= LengthOfCurrentBlock;
            } else {
                int64 NextLongerNumberPos = 1;
                int NumberLengthStep = 0;
                for (int64 j = 1; j <= i; j++) {
                    if (j == NextLongerNumberPos) {
                        NumberLengthStep++;
                        NextLongerNumberPos *= 10;
                    }
                    if (k >= NumberLengthStep) {
                        k -= NumberLengthStep;
                    } else {
                        cout << to_string(j)[k] << endl;
                        break;
                    }
                }
                break;
            }
        }
    }
    return 0;
}