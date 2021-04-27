//Cash Machine
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    int K, N;
    while (cin >> K >> N) {
        if(N==0){
            cout<<0<<endl;
            continue;
        }
        vector<int> a(N);
        vector<int> m(N);
        for (int i = 0; i < N; i++) {
            cin >> m[i] >> a[i];
        }
        if(K==0){
            cout<<0<<endl;
            continue;
        }
        vector<int> dp(K + 1, -1);
        dp[0] = 0;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j <= K; j++) {
                if (dp[j] >= 0) {
                    dp[j] = m[i];
                } else if (j < a[i] || dp[j - a[i]] <= 0) {
                    dp[j] = -1;
                } else {
                    dp[j] = dp[j - a[i]] - 1;
                }
            }
        }
        for (int i = K; i > 0; i--) {
            if (dp[i] >= 0) {
                cout << i << endl;
                break;
            }
        }
    }
    return 0;
}