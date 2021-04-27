// Cleaning Shifts

#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;
#define MAX_N 10000 + 16
#define INF 0x3f3f3f3f
class RangeMinimumQuery {
    int size;
    int dat[1 << 18];
    // min of range[a,b)
    int query(int a, int b, int k, int l, int r) {
        if (r <= a || b <= l)
            return INF;
        if (a <= l && r <= b)
            return dat[k];
        return min(query(a, b, k * 2 + 1, l, (l + r) / 2),
                   query(a, b, k * 2 + 2, (l + r) / 2, r));
    }

public:
    void init(int n) {
        size = 1;
        while (size < n) {
            size *= 2;
        }
        memset(dat, 0x3f, sizeof(int) * size * 2);
    }

    // set value[k] = a
    void update(int k, int a) {
        k += size - 1;
        dat[k] = a;
        while (k > 0) {
            k = (k - 1) / 2;
            dat[k] = min(dat[k * 2 + 1], dat[k * 2 + 2]);
        }
    }
    // min of range[a,b)
    int query(int a, int b) { return query(a, b, 0, 0, size); }

    // get value[k]
    int get(int k) { return dat[k + size]; }
} rmq;

struct Cow {
    int start, end, salary;
    bool operator<(const Cow &other) const { return start < other.start; }
} cow[MAX_N];

int main() {
    int N, M, E;
    scanf("%d %d %d", &N, &M, &E);
    E -= M;

    for (int i = 0; i < N; i++) {
        scanf("%d %d %d", &cow[i].start, &cow[i].end, &cow[i].salary);
        cow[i].start = max(0, cow[i].start - M) + 1;
        cow[i].end = max(0, cow[i].end - M) + 1;
    }
    rmq.init(E + 1);
    rmq.update(0, 0);

    sort(cow, cow + N);

    for (int i = 0; i < N; i++) {
        rmq.update(cow[i].end, min(rmq.get(cow[i].end - 1),
                                   rmq.query(cow[i].start - 1, cow[i].end + 1) +
                                       cow[i].salary));
    }

    printf("%d\n", rmq.get(E) == INF ? -1 : rmq.get(E));
    return 0;
}