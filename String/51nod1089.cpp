// 最长回文子串

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
int main() {
    string os, s = "#";
    cin >> os;
    for (size_t i = 0; i < os.size(); i++) {
        s += os[i];
        s += '#';
    }
    int n = s.size();
    vector<int> manacher(n);
    for (int i = 0, l = 0, r = -1; i < n; i++) {
        int k = (i > r) ? 1 : min(manacher[l + r - i], r - i);
        while (0 <= i - k && i + k < n && s[i - k] == s[i + k]) {
            k++;
        }
        manacher[i] = k--;
        if (i + k > r) {
            l = i - k;
            r = i + k;
        }
    }
    cout << *max_element(manacher.begin(), manacher.end()) - 1 << endl;
}