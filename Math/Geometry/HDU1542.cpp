#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
#define SIZE 50010
#define rep(i, a, b) for (int i = a; i <= b; ++i)
#define ll long long
#define mp make_pair
#define pi acos(-1.0)
#define eps 1e-7
using namespace std;
#define ls (rt << 1)    //左儿子
#define rs (rt << 1 | 1)    //右儿子
ll maxn = 4e18;
using namespace std;
ll n, m, cnt = 0;
double ans = 0, xa, ya, xb, yb;
double val[SIZE];
double pos[SIZE];
struct SegTree {
    ll l, r;
    ll cnt;
    double len;
}T[SIZE];

struct Node {
    double x, yh, yl;    //yh means y_high; yl means y_low.
    int flag;
}e[SIZE];

void push_up(ll rt) {
    if ((T[rt].l == maxn && T[rt].r == maxn)) return;
    if (T[rt].cnt) T[rt].len = val[T[rt].r + 1] - val[T[rt].l];
    else T[rt].len = T[ls].len + T[rs].len;
}

void build_tree(ll rt, ll l, ll r) {
    T[rt].l = l, T[rt].r = r;
    if (l == r) return;
    ll mid = (T[rt].l + T[rt].r) >> 1;
    build_tree(ls, l, mid);
    build_tree(rs, mid + 1, r);
}

void add(ll rt, ll l, ll r, ll v) {
    if (l <= T[rt].l && T[rt].r <= r) {
        T[rt].cnt += v;
        push_up(rt);
        return;
    }
    ll mid = (T[rt].l + T[rt].r) >> 1;
    if (l <= mid) add(ls, l, r, v);
    if (mid < r) add(rs, l, r, v);
    push_up(rt);
}

bool cmp(Node a, Node b) {
    if (a.x != b.x) return a.x < b.x;
    return a.flag > b.flag;
}

int main() {
    int num = 1;
    while (~scanf("%lld", &n)) {
        if (!n) return 0;
        ans = cnt = 0;
        rep(i, 0, SIZE - 1) {
            T[i].cnt = T[i].l = T[i].len = T[i].r = 0;
            e[i].flag = e[i].x = e[i].yh = e[i].yl = 0;
            val[i] = pos[i] = 0;
        }
        rep(i, 1, n) {
            scanf("%lf %lf %lf %lf", &xa, &ya, &xb, &yb);
            e[(i << 1) - 1].x = xa, e[i << 1].x = xb;
            e[(i << 1) - 1].yh = e[i << 1].yh = yb;
            e[(i << 1) - 1].yl = e[i << 1].yl = ya;
            e[(i << 1) - 1].flag = 1, e[i << 1].flag = -1;
            pos[++cnt] = ya; pos[++cnt] = yb;
        }
        sort(pos + 1, pos + 1 + n + n);
        cnt = unique(pos + 1, pos + n + n + 1) - pos - 1;
        rep(i, 1, n + n) {    //离散化
            ll pos1 = lower_bound(pos + 1, pos + cnt + 1, e[i].yh) - pos;
            ll pos2 = lower_bound(pos + 1, pos + cnt + 1, e[i].yl) - pos;    //在数组中二分查找位置
            val[pos1] = e[i].yh;
            val[pos2] = e[i].yl;
            e[i].yh = pos1;
            e[i].yl = pos2;
        }
        sort(e + 1, e + 1 + n + n, cmp);
        build_tree(1, 1, n + n);
        rep(i, 1, n + n) {
            add(1, e[i].yl, e[i].yh - 1, e[i].flag);
            ans += T[1].len * (e[i + 1].x - e[i].x);//根节点的len值*与下一条线段的距离=这一块内的矩形面积
        }
        printf("Test case #%d\n", num++);
        printf("Total explored area: %.2lf\n\n", ans);
    }
}
