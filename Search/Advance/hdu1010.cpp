// Tempter of the Bone

#include <cmath>
#include <cstdio>
#include <cstring>
#include <stack>
using namespace std;

const char START = 'S';
const char TARGET = 'D';
const char BLANK = '.';
const char BLOCK = 'X';
const int MAXROW = 10;
const int MAXCOL = 10;
char Map[MAXROW][MAXCOL];
bool Vis[MAXROW][MAXCOL];
int Row, Col, Time, Start_X, Start_Y, Target_X, Target_Y;

void read() {
    for (int i = 0; i < Row; i++) {
        scanf("%s", Map[i]);
        for (int j = 0; j < Col; j++) {
            if (Map[i][j] == START) {
                Start_X = j;
                Start_Y = i;
            } else if (Map[i][j] == TARGET) {
                Target_X = j;
                Target_Y = i;
            }
        }
    }
}

const int LEFT = -1, RIGHT = 1, UP = -10, DOWN = 10;
const int DIRS[] = {LEFT, RIGHT, UP, DOWN};
bool reachable(const int x, const int y) {
    if (x < 0 || x >= Col || y < 0 || y >= Row || Vis[y][x] ||
        Map[y][x] == BLOCK) {
        return false;
    }
    return true;
}

bool dfs(int timetick, int pos_x, int pos_y) {
    const int ans = Time - timetick - abs(pos_x - Target_X) + abs(pos_y - Target_Y);
    if (ans < 0 || ans % 2 == 1)
        return false;
    if (timetick == Time && pos_x == Target_X && pos_y == Target_Y)
        return true;
    for (int i = 0; i < 4; i++) {
        const int destX = pos_x + DIRS[i] % 10;
        const int destY = pos_y + DIRS[i] / 10;
        if (reachable(destX, destY)) {
            Vis[destY][destX] = true;
            if (dfs(timetick + 1, destX, destY)) {
                return true;
            }
            Vis[destY][destX] = false;
        }
    }
    return false;
}

void solve() {
    memset(Vis, false, sizeof(Vis));
    Vis[Start_Y][Start_X] = true;
    printf("%s\n", dfs(0, Start_X, Start_Y) ? "YES" : "NO");
}

int main() {
    while (scanf("%d%d%d", &Row, &Col, &Time) != EOF) {
        if (Row == 0 && Col == 0 && Time == 0)
            break;
        read();
        solve();
    }
}