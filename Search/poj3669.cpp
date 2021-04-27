// Meteor Shower
#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;
const int MAX_N = 310;
const int Safe = 1e9;
struct B {
    int x, y, Time;
};

int main() {
    ios::sync_with_stdio(false);
    cout.tie(NULL);
    cin.tie(NULL);
    int n;
    cin >> n;
    vector<vector<bool> > vis(MAX_N, vector<bool>(MAX_N));
    vector<vector<int> > Map(MAX_N, vector<int>(MAX_N, Safe));
    int dir[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    for (int i = 0, x, y, t; i < n; i++) {
        cin >> x >> y >> t;
        Map[x][y] = min(Map[x][y], t);
        for (int k = 0; k < 4; k++) {
            int ti = x + dir[k][0], tj = y + dir[k][1];
            if (0 <= ti && 0 <= tj)
                Map[ti][tj] = min(Map[ti][tj], t);
        }
    }
    if (Map[0][0] == 0) {
        cout << -1 << endl;
        return 0;
    }
    queue<B> Move;
    Move.push({0, 0, 0});
    while (!Move.empty()) {
        B now = Move.front();
        Move.pop();
        if (Map[now.x][now.y] == Safe) {
            cout << now.Time << endl;
            return 0;
        }
        for (int k = 0; k < 4; k++) {
            int i = now.x + dir[k][0];
            int j = now.y + dir[k][1];
            if (i < 0 || j < 0 || vis[i][j])
                continue;
            if (now.Time + 1 < Map[i][j]) {
                Move.push({i, j, now.Time + 1});
                vis[i][j] = true;
            }
        }
    }
    cout << -1 << endl;
    return 0;
}