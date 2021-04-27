// DNA Sequence

#include<cstdio>
#include<cstring>
#include<queue>
using namespace std;
int Ch[111][4], Fail[111], Tn;
bool Flag[111];

int Idx[128];

void Insert(const char *s) {
    int x = 0;
    for (int i = 0; s[i]; ++i) {
        int y = Idx[s[i]];
        if (Ch[x][y] == 0)
            Ch[x][y] = ++Tn;
        x = Ch[x][y];
    }
    Flag[x] = true;
}

void Init() {
    memset(Fail, 0, sizeof(Fail));
    queue<int> que;
    for (int i = 0; i < 4; ++i) {
        if (Ch[0][i])
            que.push(Ch[0][i]);
    }
    while (!que.empty()) {
        const int now = que.front();
        que.pop();
        for (int i = 0; i < 4; ++i) {
            if (Ch[now][i])
                que.push(Ch[now][i]), Fail[Ch[now][i]] = Ch[Fail[now]][i];
            else
                Ch[now][i] = Ch[Fail[now]][i];
            Flag[Ch[now][i]] |= Flag[Ch[Fail[now]][i]];
        }
    }
}

struct Mat {
    long long mat[111][111]{};
    Mat() {
        memset(mat, 0, sizeof(mat));
    }
};

Mat operator*(const Mat &m1, const Mat &m2) {
    Mat m;
    for (int i = 0; i <= Tn; ++i) {
        for (int j = 0; j <= Tn; ++j) {
            for (int k = 0; k <= Tn; ++k) {
                m.mat[i][j] += m1.mat[i][k] * m2.mat[k][j];
                m.mat[i][j] %= 100000;
            }
        }
    }
    return m;
}

int main() {
    Idx['A'] = 0;
    Idx['C'] = 1;
    Idx['T'] = 2;
    Idx['G'] = 3;
    char str[11];
    int m, n;
    while (~scanf("%d%d", &m, &n)) {
        Tn = 0;
        memset(Flag, 0, sizeof(Flag));
        memset(Ch, 0, sizeof(Ch));
        while (m--) {
            scanf("%s", str);
            Insert(str);
        }
        Init();
        Mat e, x;
        for (int i = 0; i <= Tn; ++i)
            e.mat[i][i] = 1;
        for (int i = 0; i <= Tn; ++i) {
            if (Flag[i])
                continue;
            for (int j = 0; j < 4; ++j) {
                if (Flag[Ch[i][j]])
                    continue;
                ++x.mat[i][Ch[i][j]];
            }
        }
        while (n) {
            if (n & 1)
                e = e * x;
            x = x * x;
            n >>= 1;
        }
        long long res = 0;
        for (int i = 0; i <= Tn; ++i) {
            res += e.mat[0][i];
            res %= 100000;
        }
        printf("%lld\n", res);
    }
    return 0;
}
