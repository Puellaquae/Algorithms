//"Dynmaic" Inversion

#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
#define MAX_N 200000 + 16
#define MAX_M 100000 + 16
#define BUCKET_SIZE 450 // sqrt(MAX_N) = 447

int A[MAX_N], N, M;
struct Bucket {
    int count;      // 内部数字的个数
    int prefix_sum; // 前缀和
} bucket[BUCKET_SIZE][BUCKET_SIZE];

// 平面坐标快速查询
struct Space {
    int X[MAX_N], Y[MAX_N];

    void insert(const int &x, const int &y) {
        X[y] = x;
        Y[x] = y;
    }

    void remove(const int &x, const int &y) {
        X[y] = -1;
        Y[x] = -1;
    }

    int getX(const int &y) { return X[y]; }

    int getY(const int &x) { return Y[x]; }
    void init() {
        memset(X, -1, sizeof(X));
        memset(Y, -1, sizeof(Y));
    }
} space;

void update_prefix_sum(int bx, int by) {
    int sum = (bx > 0 ? bucket[bx - 1][by].prefix_sum : 0);
    for (int i = bx; i < BUCKET_SIZE; ++i) {
        sum += bucket[i][by].count;
        bucket[i][by].prefix_sum = sum;
    }
}

// 加入一个点
void add(int x, int y) {
    space.insert(x, y);
    int bx = x / BUCKET_SIZE;
    int by = y / BUCKET_SIZE;

    ++bucket[bx][by].count;
    update_prefix_sum(bx, by);
}

// 删除一个点
void remove(int x, int y) {
    space.remove(x, y);
    int bx = x / BUCKET_SIZE;
    int by = y / BUCKET_SIZE;

    --bucket[bx][by].count;
    update_prefix_sum(bx, by);
}

// (0,0)与(x,y)围起来的矩形区域的点的个数
int count_sum(int x, int y) {
    int block_w = (x + 1) / BUCKET_SIZE;
    int block_h = (y + 1) / BUCKET_SIZE;

    int count = 0;
    // 完全在内部的桶
    for (int i = 0; i < block_h; ++i) {
        if (block_w > 0) {
            count += bucket[block_w - 1][i].prefix_sum;
        }
    }
    // 其他
    for (int i = block_w * BUCKET_SIZE; i <= x; ++i) {
        if (space.getY(i) != -1 && space.getY(i) < block_h * BUCKET_SIZE)
            count++;
    }
    for (int i = block_h * BUCKET_SIZE; i <= y; ++i) {
        if (space.getX(i) != -1 && space.getX(i) <= x)
            count++;
    }
    return count;
}

// (x,y)的左上和右下方块内部点的个数就是逆序数对的个数
int count_inversion(int x, int y) {
    int count = 0;
    int intersection = count_sum(x, y);
    count += count_sum(x, N - 1) - intersection; // 左上
    count += count_sum(N - 1, y) - intersection; // 右下
    return count;
}

int main() {
    while (~scanf("%d %d", &N, &M)) {
        space.init();
        memset(bucket, 0, sizeof(bucket));
        for (int i = 0; i < N; ++i) {
            scanf("%d", &A[i]);
            --A[i];
        }
        long long inversion = 0;
        for (int i = 0; i < N; ++i) {
            add(i, A[i]);
            inversion += count_inversion(i, A[i]);
        }
        for (int i = 0; i < M; ++i) {
            int q;
            scanf("%d", &q);
            --q;
            printf("%lld\n", inversion);
            inversion -= count_inversion(space.getX(q), q);
            remove(space.getX(q), q);
        }
    }
    return 0;
}