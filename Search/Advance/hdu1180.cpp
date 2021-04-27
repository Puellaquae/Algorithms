// 诡异的楼梯

#include <cmath>
#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;

const char V_LADDER = '|';
const char H_LADDER = '-';
const char START = 'S';
const char TARGET = 'T';
const char BLANK = '.';
const char BLOCK = '*';
const int MAXROW = 22;
const int MAXCOL = 22;
char Map[MAXROW][MAXCOL];
bool Vis[MAXROW][MAXCOL];
int Row, Col, Start_X, Start_Y, Target_X, Target_Y;
struct Content {
    int timetick, pos_x, pos_y;
    bool operator<(const Content &b) const { return timetick > b.timetick; }
};

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

void go(const int dir, priority_queue<Content> &q, const Content &cur) {
    const int destX = cur.pos_x + dir % 10;
    const int destY = cur.pos_y + dir / 10;
    if (destX < 0 || destX >= Col || destY < 0 || destY >= Row ||
        Vis[destY][destX])
        return;
    switch (Map[destY][destX]) {
    case BLOCK:
        return;
    case TARGET:
    case BLANK:
        q.push(Content{cur.timetick + 1, destX, destY});
        Vis[destY][destX] = true;
        return;
    case H_LADDER:
    case V_LADDER: {
        const char curLadder =
            ((Map[destY][destX] == V_LADDER) + cur.timetick) % 2 == 0
                ? H_LADDER
                : V_LADDER;
        int waitTime = 1;
        if (dir % 10 != 0 && curLadder == V_LADDER ||
            dir / 10 != 0 && curLadder == H_LADDER) {
            waitTime++;
            //q.push(Content{cur.timetick + 1, cur.pos_x, cur.pos_y});
            //return;
        }
        const int afterX = destX + dir % 10;
        const int afterY = destY + dir / 10;
        if (afterX < 0 || afterX >= Col || afterY < 0 || afterY >= Row ||
            Vis[afterY][afterX] || Map[afterY][afterX] == BLOCK) {
            return;
        }
        q.push(Content{cur.timetick + waitTime, afterX, afterY});
        Vis[afterY][afterX] = true;
        return;
    }
    default:
        break;
    }
}

void debug_show(const Content &cur) {
    system("cls");
    for (int i = 0; i < Row; i++) {
        for (int j = 0; j < Col; j++) {
            if (i == cur.pos_y && j == cur.pos_x)
                putchar('@');
            else if (Map[i][j] == H_LADDER)
                putchar(cur.timetick % 2 == 0 ? H_LADDER : V_LADDER);
            else if (Map[i][j] == V_LADDER)
                putchar(cur.timetick % 2 == 0 ? V_LADDER : H_LADDER);
            else
                putchar(Map[i][j]);
        }
        puts("");
    }
    printf("time:%d, (%d, %d), p:%d\n", cur.timetick, cur.pos_x, cur.pos_y,
           cur.timetick + abs(cur.pos_x - Target_X) +
               abs(cur.pos_y - Target_Y));
    // system("pause");
}

int main() {
    while (scanf("%d%d", &Row, &Col) != EOF) {
        read();
        memset(Vis, false, sizeof(Vis));
        priority_queue<Content> Q;
        Q.push(Content{0, Start_X, Start_Y});
        Vis[Start_Y][Start_X] = true;
        while (!Q.empty()) {
            const Content cur = Q.top();
            Q.pop();
            // debug_show(cur);
            if (cur.pos_x == Target_X && cur.pos_y == Target_Y) {
                printf("%d\n", cur.timetick);
                break;
            }
            go(LEFT, Q, cur);
            go(RIGHT, Q, cur);
            go(UP, Q, cur);
            go(DOWN, Q, cur);
        }
    }
}