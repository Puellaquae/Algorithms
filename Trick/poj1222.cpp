// EXTENDED LIGHTS OUT
#include <cstring>
#include <iostream>
int L[5][6];
int StoreL[5][6];
using namespace std;
void flip(int i, int j) {
    L[i][j] = 1 - L[i][j];
    if (i >= 1)
        L[i - 1][j] = 1 - L[i - 1][j];
    if (i <= 3)
        L[i + 1][j] = 1 - L[i + 1][j];
    if (j >= 1)
        L[i][j - 1] = 1 - L[i][j - 1];
    if (j <= 4)
        L[i][j + 1] = 1 - L[i][j + 1];
}
int main() {
    ios::sync_with_stdio(false);
    cout.tie(NULL);
    cin.tie(NULL);
    int t;
    cin >> t;
    for (int sharp = 1; sharp <= t; sharp++) {
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 6; j++) {
                cin >> StoreL[i][j];
            }
        }
        int MinStep = 100;
        int MinFlip[5][6];
        int Flip[5][6];
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 6; j++) {
                MinFlip[i][j] = 0;
            }
        }
        for (int E = 0; E < (1 << 6); E++) {
            int step = 0;
            for (int i = 0; i < 5; i++) {
                for (int j = 0; j < 6; j++) {
                    Flip[i][j] = 0;
                }
            }
            for (int i = 0; i < 5; i++) {
                for (int j = 0; j < 6; j++) {
                    L[i][j] = StoreL[i][j];
                }
            }
            for (int j = 0; j < 6; j++) {
                if (E & (1 << j)) {
                    flip(0, j);
                    Flip[0][j] = 1;
                    step++;
                }
            }
            for (int i = 1; i < 5; i++) {
                for (int j = 0; j < 6; j++) {
                    if (L[i - 1][j]) {
                        flip(i, j);
                        Flip[i][j] = 1;
                        step++;
                    }
                }
            }
            bool AllOff = true;
            for (int i = 0; i < 5; i++) {
                for (int j = 0; j < 6; j++) {
                    if (L[i][j]) {
                        AllOff = false;
                    }
                }
            }
            if (AllOff&&step < MinStep) {
                MinStep = step;
                memcpy(MinFlip, Flip, sizeof(Flip));
            }
        }
        cout << "PUZZLE #" << sharp << "\n";
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 6; j++) {
                cout << MinFlip[i][j] << ' ';
            }
            cout << '\n';
        }
    }
}