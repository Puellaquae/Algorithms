//Tokitsukaze, CSL and Stone Game

#include <algorithm>
#include <iostream>
#include <iterator>

const int MAX_N = 100000 + 50;
int Stones[MAX_N];
using namespace std;
bool Game(const int n) {
    copy_n(istream_iterator<int>(cin), n, Stones);
    sort(Stones, Stones + n);
    if (Stones[0] == 0 && Stones[1] == 0)
        return false;
    for (int i = 0; i < n - 1; i++) {
        if (Stones[i + 1] == Stones[i]) {
            for (int j = i + 1; j < n - 1; j++) {
                if (Stones[j + 1] == Stones[j])
                    return false;
            }
            if (i >= 1 && Stones[i - 1] == Stones[i] - 1)
                return false;
            break;
        }
    }
    int ans = 0;
    for (int i = 0; i < n; i++)
        ans += Stones[i] - i;
    return ans % 2 != 0;
}
int main() {
    int n;
    cin >> n;
    cout << (Game(n) ? "sjfnb\n" : "cslnb\n");
}