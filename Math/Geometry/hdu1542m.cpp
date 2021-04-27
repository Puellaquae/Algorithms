// Atlantis

#include <cstdio>
#ifndef INT_MAX
#    define INT_MAX 0x7fffffff
#endif
template <typename T, int N> class SegTreeInBook {
    int n;
    std::vector<T> dat;
    T (*cmp)(T, T);

public:
    SegTreeInBook(T (*cmp_)(T, T)) : cmp(cmp_) {
        n = 1;
        while (n < N) {
            n *= 2;
        }
        dat(2 * n);
        for (int i = 0; i < 2 * n - 1; i++) {
            dat[i] = INT_MAX;
        }
    }
    void update(int k, T a) {
        k += n - 1;
        dat[k] = a;
        while (k > 0) {
            k = (k - 1) / 2;
            dat[k] = cmp(dat[k * 2 + 1], dat[k * 2 + 2]);
        }
    }

    T query(int a, int b, int k = 0, int l = 0, int r = N) {
        if (r <= a || b <= l) {
            return dat[k];
        } else {
            T v1 = query(a, b, k * 2 + 1, 1, (l + r) / 2);
            T v2 = query(a, b, k * 2 + 2, (l + r) / 2, r);
            return cmp(v1, v2);
        }
    }
};

using namespace std;
int main() {
    int n;
    scanf("%d", &n);
}