// Linear world
// Why G++ wil TLE, while C++ not
#include <algorithm>
#include <cstdio>
#include <iostream>
#include <iomanip>
using namespace std;
struct Create {
    char dir;
    double pos;
    char name[255];
    bool operator<(const Create& x) const { return pos < x.pos; }
} Creates[32005];
int main() {
    ios::sync_with_stdio(false);
    cout.tie(NULL);
    cin.tie(NULL);
    int n;
    while (cin >> n && n) {
        double l, v;
        cin >> l >> v;
        for (int i = 0; i < n; i++) {
            cin >> Creates[i].dir >> Creates[i].pos >> Creates[i].name;
        }
        sort(Creates, Creates+n);
        int IndexOfLLCreate = 0;
        int DirOfLLCreate = 1;
        double LongestLength = 0;
        for (int i = 0; i < n; i++) {
            if (Creates[i].dir == 'n' || Creates[i].dir == 'N') {
                if (Creates[i].pos > LongestLength) {
                    LongestLength = Creates[i].pos;
                    IndexOfLLCreate = i;
                    DirOfLLCreate = 0;
                }
            }
            else {
                if (l - Creates[i].pos > LongestLength) {
                    LongestLength = l - Creates[i].pos;
                    IndexOfLLCreate = i;
                    DirOfLLCreate = 1;
                }
            }
        }
        int SwapCount = 0;
        if (DirOfLLCreate==1) {
            for (int i = IndexOfLLCreate; i < n; i++) {
                if (Creates[i].dir == 'n' || Creates[i].dir == 'N') {
                    SwapCount++;
                }
            }
            IndexOfLLCreate += SwapCount;
        }
        else {
            for (int i = IndexOfLLCreate; i >= 0; i--) {
                if (Creates[i].dir == 'p' || Creates[i].dir == 'P') {
                    SwapCount++;
                }
            }
            IndexOfLLCreate -= SwapCount;
        }
        LongestLength /= v;
        cout << fixed << setw(13) << setprecision(2) << int(LongestLength * 100) / 100.0 << " " << Creates[IndexOfLLCreate].name << '\n';
    }
    return 0;
}