#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>
using namespace std;

const int DIRS[4][2]{{-1, 0}, {0, -1}, {1, 0}, {0, 1}};
int N, Time;

struct Rabbit {
    int d, s, t, x, y;
};

int Dirs(const char d) {
    if (d == 'N')
        return 0;
    if (d == 'W')
        return 1;
    if (d == 'S')
        return 2;
    if (d == 'E')
        return 3;
}

void Action(Rabbit &rabbit) {
    const int nx = rabbit.x + rabbit.s * DIRS[rabbit.d][0];
    const int ny = rabbit.y + rabbit.s * DIRS[rabbit.d][1];

    if (nx > 0 && nx <= N && ny > 0 && ny <= N) {
        rabbit.x = nx;
        rabbit.y = ny;
    } else {
        if (rabbit.d == 0) {
            rabbit.x += rabbit.s - 2 * (rabbit.x - 1);
        } else if (rabbit.d == 1) {
            rabbit.y += rabbit.s - 2 * (rabbit.y - 1);
        } else if (rabbit.d == 2) {
            rabbit.x -= rabbit.s - 2 * (N - rabbit.x);
        } else {
            rabbit.y -= rabbit.s - 2 * (N - rabbit.y);
        }
        rabbit.d = (rabbit.d + 2) % 4;
    }
}

int main() {
    while (cin >> N && N) {
        Rabbit tom, jetty;
        string d;
        cin >> d >> tom.s >> tom.t;
        tom.d = Dirs(d[0]);
        tom.x = tom.y = 1;
        cin >> d >> jetty.s >> jetty.t;
        jetty.d = Dirs(d[0]);
        jetty.x = jetty.y = N;
        cin >> Time;
        for (int t = 1; t <= Time; t++) {
            Action(tom);
            Action(jetty);
            if (tom.x == jetty.x && tom.y == jetty.y) {
                swap(tom.d, jetty.d);
            } else {
                if (t % tom.t == 0) {
                    tom.d = (tom.d + 1) % 4;
                }
                if (t % jetty.t == 0) {
                    jetty.d = (jetty.d + 1) % 4;
                }
            }
        }
        cout << tom.x << " " << tom.y << endl;
        cout << jetty.x << " " << jetty.y << endl;
    }
}
