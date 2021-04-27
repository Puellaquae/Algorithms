#include <iostream>
#include <queue>
#include <vector>
// 迷宫问题

using namespace std;
int m[25];
int main() {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            cin >> m[i * 5 + j];
        }
    }
    queue<vector<int> > Q;
    Q.push(vector<int>(1, 0));
    while (!Q.empty()) {
        vector<int> cur = Q.front();
        Q.pop();
        if (0 > cur.back() || cur.back() >= 25 || m[cur.back()] == 1) {
            continue;
        }
        if (cur.back() == 24) {
            for (int i = 0; i < cur.size(); i++) {
                printf("(%d, %d)\n", cur[i] / 5, cur[i] % 5);
            }
            return 0;
        }
        if (cur.back() % 5 > 0) {
            vector<int> left = cur;
            left.push_back(cur.back() - 1);
            Q.push(left);
        }
        if (cur.back() % 5 < 4) {
            vector<int> right = cur;
            right.push_back(cur.back() + 1);
            Q.push(right);
        }
        vector<int> up = cur;
        up.push_back(cur.back() - 5);
        Q.push(up);
        vector<int> down = cur;
        down.push_back(cur.back() + 5);
        Q.push(down);
    }
}