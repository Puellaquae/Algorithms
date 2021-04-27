#include <iostream>
using namespace std;

bool FaceSame(const int a, const int b, const int c, const int d) {
    return a == b && b == c && c == d;
}

bool HexaFaceSame(
        const int a, const int b, const int c, const int d,
        const int e, const int f, const int g, const int h,
        const int i, const int j, const int k, const int l,
        const int m, const int n, const int o, const int p,
        const int q, const int r, const int s, const int t,
        const int u, const int v, const int w, const int x
        ) {
    return
            FaceSame(a, b, c, d) &&
            FaceSame(e, f, g, h) &&
            FaceSame(i, j, k, l) &&
            FaceSame(m, n, o, p) &&
            FaceSame(q, r, s, t) &&
            FaceSame(u, v, w, x);
}

int main() {
    int T, a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x;
    cin >> T;
    while (T--) {
        cin
                >> a >> b >> c >> d
                >> e >> f >> g >> h
                >> i >> j >> k >> l
                >> m >> n >> o >> p
                >> q >> r >> s >> t
                >> u >> v >> w >> x;
        if (
            HexaFaceSame(
                a, b, c, d, 
                e, f, g, h,
                i, j, k, l,
                m, n, o, p,
                q, r, s, t,
                u, v, w, x) ||
            HexaFaceSame(
                b, d, a, c,
                r, t, g, h,
                i, j, k, l,
                m, n, u, w,
                q, p, s, o,
                f, v, e, x) ||
            HexaFaceSame(
                c, a, d, b,
                w, u, g, h,
                i, j, k, l,
                m, n, t, r,
                q, e, s, f,
                o, v, p, x) ||
            HexaFaceSame(
                m, b, o, d,
                a, f, c, h,
                e, j, g, l,
                i, n, k, p,
                s, q, t, r,
                u, v, w, x) ||
            HexaFaceSame(
                e, b, g, d,
                i, f, k, h,
                m, j, o, l,
                a, n, c, p,
                r, t, q, s,
                u, v, w, x) ||
            HexaFaceSame(
                u, v, c, d,
                e, f, g, h,
                i, j, r, q,
                o, m, p, n,
                a, b, s, t,
                l, k, w, x) ||
            HexaFaceSame(
                q, r, c, d,
                e, f, g, h,
                i, j, v, u,
                n, p, m, o,
                l, k, s, t,
                a, b, w, x)
        ) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }
}