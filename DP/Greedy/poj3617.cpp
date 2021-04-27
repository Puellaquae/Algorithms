// Best Cow Line
//Using Greedy algorithm
#include <algorithm>
#include <cstdio>
#include <iostream>
#include <string>
using namespace std;
int main() {
    int n;
    cin >> n;
    string s;
    while (n--) {
        char x;
        cin >> x;
        s += x;
    }
    int l = 0, r = s.size() - 1, c = 0;
    while (l <= r) {
        bool left = true;
        for (int i = 0; l + i <= r; i++) {
            if (s[l + i] < s[r - i]) {
                left = true;
                break;
            } else if (s[l + i] > s[r - i]) {
                left = false;
                break;
            }
        }
        if (left) {
            putchar(s[l]);
            l++;
        } else {
            putchar(s[r]);
            r--;
        }
        c++;
        if (c % 80 == 0) {
            putchar('\n');
        }
    }
    return 0;
}