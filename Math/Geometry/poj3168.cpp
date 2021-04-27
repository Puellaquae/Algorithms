//Barn Expansion

#include <algorithm>
#include <cstdio>
#include <string>
#include <vector>
#include <cstring>
using namespace std;

enum PointType { START, END };

struct Point {
    int ord;
    int pos;
    int id;
    PointType type;
    bool operator<(const Point &other) const {
        if (ord != other.ord)
            return ord < other.ord;
        if (pos != other.pos)
            return pos < other.pos;
        return type < other.type;
    }
};

Point verticals[200000], horizontals[200000];
int N;
bool ok[25000];

void scan(const Point *start, const Point *end) {
    int share_count = 0;
    const Point *t = start;
    int prev_ord = -1;
    bool invalid = false;
    while (t != end) {
        if (t->ord != prev_ord) {
            share_count = 0;
            invalid = false;
            prev_ord = t->ord;
        }
        const int pos = t->pos;
        for (; t != end && t->pos == pos && t->ord == prev_ord; t++) {
            if (invalid)
                ok[t->id] = false;
            if (t->type == START) {
                share_count++;
                if (share_count >= 2)
                    invalid = true;
            }
            if (t->type == END) {
                share_count--;
                if (share_count == 0)
                    invalid = false;
            }
        }
    }
}

void solve() {}

int main() {
    scanf("%d", &N);
    for (int i = 0, A, B, C, D; i < N; ++i) {
        scanf("%d %d %d %d", &A, &B, &C, &D);
        verticals[i * 4] = Point{A, B, i, START};
        verticals[i * 4 + 1] = Point{A, D, i, END};
        verticals[i * 4 + 2] = Point{C, B, i, START};
        verticals[i * 4 + 3] = Point{C, D, i, END};
        horizontals[i * 4] = Point{B, A, i, START};
        horizontals[i * 4 + 1] = Point{B, C, i, END};
        horizontals[i * 4 + 2] = Point{D, A, i, START};
        horizontals[i * 4 + 3] = Point{D, C, i, END};
    }
    sort(verticals, verticals + N * 4);
    sort(horizontals, horizontals + N * 4);
    memset(ok, 1, sizeof(ok));
    scan(verticals, verticals + N * 4);
    scan(horizontals, horizontals + N * 4);
    printf("%d\n", count(ok, ok + N, true));
    return 0;
}