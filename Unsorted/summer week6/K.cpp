#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>
#include <vector>
using namespace std;

const int STEP[4][2]{{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

int Dirs(const char d) {
    if (d == 'N')
        return 0;
    if (d == 'E')
        return 1;
    if (d == 'S')
        return 2;
    if (d == 'W')
        return 3;
}

struct Robot {
    int x, y, dir;
};

int main() {
    int k, w, h, n, m;
    cin >> k;
    while (k--) {
        cin >> w >> h >> n >> m;
        vector<vector<int>> grid(h + 1, vector<int>(w + 1, 0));
        vector<Robot> robots(n + 1);
        for (int i = 1; i <= n; i++) {
            char dir;
            cin >> robots[i].x >> robots[i].y >> dir;
            robots[i].dir = Dirs(dir);
            grid[robots[i].y][robots[i].x] = i;
        }
        int id, repeat;
        char action;
        bool finflag = false;
        while (m--) {
#ifdef _DEBUG
            system("cls");
            for (int j = 0; j <= w; j++) {
                printf("%02d", j);
            }
            puts("");
            for (int i = h; i > 0; i--) {
                printf("%02d", i);
                for (int j = 1; j <= w; j++) {
                    if (grid[i][j]) {
                        printf("%d%c", grid[i][j], "A>v<"[robots[grid[i][j]].dir]);
                    } else {
                        printf(" .");
                    }
                }
                puts("");
            }
#endif
            cin >> id >> action >> repeat;
            if (finflag)
                continue;
            if (action == 'L') {
                robots[id].dir = (robots[id].dir + 3 * repeat) % 4;
            } else if (action == 'R') {
                robots[id].dir = (robots[id].dir + repeat) % 4;
            } else {
                while (repeat--) {
                    const int nx = robots[id].x + STEP[robots[id].dir][0];
                    const int ny = robots[id].y + STEP[robots[id].dir][1];
                    if (w < nx || nx <= 0 || h < ny || ny <= 0) {
                        finflag = true;
                        printf("Robot %d crashes into the wall\n", id);
                        break;
                    }
                    if (grid[ny][nx]) {
                        finflag = true;
                        printf("Robot %d crashes into robot %d\n", id, grid[ny][nx]);
                        break;
                    }
                    grid[robots[id].y][robots[id].x] = 0;
                    robots[id].y = ny;
                    robots[id].x = nx;
                    grid[ny][nx] = id;
                }
            }
        }
        if (!finflag) {
            printf("OK\n");
        }
    }
}
