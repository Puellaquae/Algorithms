// The Water Bowls
#include <iostream>
using namespace std;
int main() {
    static int A[20];
    static int B[20];
    for (int i = 0; i < 20; i++) {
        cin >> A[i];
        B[i] = A[i];
    }
    int stepA = 0;
    for (int i = 1; i < 20; i++) {
        if (A[i - 1]) {
            A[i - 1] = 1 - A[i - 1];
            A[i] = 1 - A[i];
            A[i + 1] = 1 - A[i + 1];
            stepA++;
        }
    }
    int stepB = 1;
    B[0] = 1 - B[0];
    B[1] = 1 - B[1];
    for (int i = 1; i < 20; i++) {
        if (B[i - 1]) {
            B[i - 1] = 1 - B[i - 1];
            B[i] = 1 - B[i];
            B[i + 1] = 1 - B[i + 1];
            stepB++;
        }
    }
    cout << (stepA < stepB ? stepA : stepB) << endl;
    return 0;
}