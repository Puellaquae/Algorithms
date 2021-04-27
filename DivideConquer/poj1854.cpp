// Evil Straw Warts Live

#include <iostream>
using namespace std;
int alpha[26] = {0};
void solve() {
    string str;
    cin >> str;
    fill_n(alpha, 26, 0);
    for (int i = 0; i < str.size(); i++) {
        alpha[str[i] - 'a']++;
    }
    bool flag = str.size() % 2 == 0;
    for (int i = 0; i < 26; i++) {
        if (alpha[i] % 2 == 1) {
            if (flag) {
                cout << "Impossible\n";
                return;
            }
            flag = true;
        }
    }
    int step = 0;
    int i = 0, j = str.size() - 1;
    for (; i < j; i++, j--) {
        int newi = i, newj = j;
        for (; newi < j; newi++) {
            if (str[newi] == str[j])
                break;
        }
        for (; newj > i; newj--) {
            if (str[newj] == str[i])
                break;
        }
        if (newi - i <= j - newj) {
            step += newi - i;
            for (int k = newi - 1; k >= i; k--) {
                swap(str[k], str[k + 1]);
            }
        } else {
            step += j - newj;
            for (int k = newj + 1; k <= j; k++) {
                swap(str[k], str[k - 1]);
            }
        }
    }
    cout << step << endl;
}
int main() {
    int t;
    cin >> t;
    while (t--)
        solve();
}