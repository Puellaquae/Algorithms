#include <algorithm>
#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

class Solution {
public:
    int longestCycle(const vector<int> &edges) {
        int n = edges.size();
        int maxL = -1;
        vector<int> vis(n, -1);
        vector<int> dis(n, -1);
        for (int i = 0; i < n; i++) {
            if (vis[i] != -1) {
                continue;
            }
            int c = i;
            int s = 0; 
            for (;;) {
                vis[c] = i;
                dis[c] = s++;
                c = edges[c];
                if (c == -1) {
                    break;
                }
                if (vis[c] == i && dis[c] != -1) {
                    maxL = max(maxL, s - dis[c]);
                    break;
                } else if (vis[c] != -1) {
                    break;
                }
            }
        }
        return maxL;
    }
};

int main() {
    Solution s;
    cout << s.longestCycle({3, 3, 4, 2, 3}) << endl;
    cout << s.longestCycle({2, -1, 3, 1}) << endl;
    cout << s.longestCycle({-1, 4, -1, 2, 0, 4}) << endl;
}