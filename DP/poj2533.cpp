//Longest Ordered Subsequence
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    int N;
    cin >> N;
    vector<int> num(N);
    for (int i = 0; i < N; i++) {
        cin >> num[i];
    }
    vector<int> dp(N, 1);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < i; j++) {
            if (num[j] < num[i]) {
                dp[i] = max(dp[i], dp[j] + 1);
            }
        }
    }
    cout << *max_element(dp.begin(), dp.end()) << endl;
    return 0;
}
