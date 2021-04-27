// Packets
// Using Greedy
#include <iostream>

using namespace std;

int main() {
    int s1, s2, s3, s4, s5, s6;
    int s3left[4] = {0, 5, 3, 1};
    while (cin >> s1 >> s2 >> s3 >> s4 >> s5 >> s6 && (s1 || s2 || s3 || s4 || s5 || s6)) {
        int ans = s6 + s5 + s4 + (s3 + 3) / 4;
        int lefts2 = s4 * 5 + s3left[s3 % 4];
        if (s2 > lefts2)
            ans += (s2 - lefts2 + 8) / 9;
        int lefts1 = ans * 36 - s6 * 36 - s5 * 25 - s4 * 16 - s3 * 9 - s2 * 4;
        if (s1 > lefts1)
            ans += (s1 - lefts1 + 35) / 36;
        cout << ans << endl;
    }
    return 0;
}