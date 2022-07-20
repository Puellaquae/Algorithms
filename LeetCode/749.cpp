#include <iostream>
#include <queue>
#include <set>
#include <vector>

using namespace std;

class Solution {
public:
    bool inQ(int x, int r) { return 0 <= x && x < r; }

    const int d[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

    int containVirus(vector<vector<int>> &isInfected) {
        int m = isInfected.size();
        int n = isInfected.front().size();
        int reqBCnt = 0;
        for (;;) {
            vector<vector<int>> vis(m, vector<int>(n, -1));
            vector<vector<int>> b(m, vector<int>(n, 0));
            int curId = 0;
            int maxInfC = 0;
            int theReqB = 0;
            int theId = 0;
            for (int i = 0; i < m; i++) {
                for (int j = 0; j < n; j++) {
                    if (vis[i][j] == -1 && isInfected[i][j] == 1) {
                        queue<pair<int, int>> q;
                        curId++;
                        int infC = 0;
                        int reqB = 0;
                        q.emplace(i, j);
                        vis[i][j] = curId;
                        while (!q.empty()) {
                            auto top = q.front();
                            q.pop();
                            for (auto s : d) {
                                int ni = top.first + s[0];
                                int nj = top.second + s[1];
                                if (inQ(ni, m) && inQ(nj, n)) {
                                    if (isInfected[ni][nj] == 1 &&
                                        vis[ni][nj] == -1) {
                                        q.emplace(ni, nj);
                                        vis[ni][nj] = curId;
                                    } else if (isInfected[ni][nj] == 0) {
                                        reqB++;
                                        if (vis[ni][nj] != curId) {
                                            infC++;
                                            b[ni][nj]++;
                                            vis[ni][nj] = curId;
                                        }
                                    }
                                }
                            }
                        }
                        if (infC > maxInfC) {
                            maxInfC = infC;
                            theReqB = reqB;
                            theId = curId;
                        }
                    }
                }
            }
            if (maxInfC == 0) {
                break;
            }
            reqBCnt += theReqB;
            for (int i = 0; i < m; i++) {
                for (int j = 0; j < n; j++) {
                    if (vis[i][j] != theId && vis[i][j] != -1) {
                        isInfected[i][j] = 1;
                    } else if (vis[i][j] == theId && b[i][j] > 1) {
                        isInfected[i][j] = 1;
                    } else if (vis[i][j] == theId && isInfected[i][j] == 1) {
                        isInfected[i][j] = 2;
                    }
                }
            }
        }
        return reqBCnt;
    }
};

int main() {
    Solution s;
    vector<vector<int>> a{{0, 1, 0, 0, 0, 0, 0, 1},
                          {0, 1, 0, 0, 0, 0, 0, 1},
                          {0, 0, 0, 0, 0, 0, 0, 1},
                          {0, 0, 0, 0, 0, 0, 0, 0}};
    cout << s.containVirus(a) << endl;
    vector<vector<int>> b{{1, 1, 1}, {1, 0, 1}, {1, 1, 1}};
    cout << s.containVirus(b) << endl;
    vector<vector<int>> c{{1, 1, 1, 0, 0, 0, 0, 0, 0},
                          {1, 0, 1, 0, 1, 1, 1, 1, 1},
                          {1, 1, 1, 0, 0, 0, 0, 0, 0}};
    cout << s.containVirus(c) << endl;
}