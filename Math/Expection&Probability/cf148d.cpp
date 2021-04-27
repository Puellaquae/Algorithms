// Bag of mice

#include <cstdio>
#include <iostream>
#include <vector>
using namespace std;
int main() {
    int w, b;
    scanf("%d%d", &w, &b);
    if (!w) {
        printf("0.000000000\n");
    } else {
        vector<vector<double> > dp(w + 2, vector<double>(b + 2, 0.0));
        for (int i = 1; i <= w; ++i)
            dp[i][0] = 1.0;
        for (int i = 1; i <= w; ++i) {
            for (int j = 1; j <= b; ++j) {
                // Catch White
                double p1 = 1.0 * i / (i + j);
                // Catch Black,White
                double p2 = 1.0 * (j - 1.0) / (i + j - 1.0);
                // Catch Black,Black, Run Black
                double p3 = 1.0 * (j - 2.0) / (i + j - 2.0);
                p3 = (1.0 - p1) * p2 * p3 * dp[i][j - 3];
                // Catch Black,Black, Run White
                double p4 = 1.0 * i / (i + j - 2.0);
                p4 = (1.0 - p1) * p2 * p4 * dp[i - 1][j - 2];

                dp[i][j] = p1 + (j >= 2 ? p4 : 0.0) + (j >= 3 ? p3 : 0.0);
            }
        }
        printf("%.9f\n", dp[w][b]);
    }
    return 0;
}