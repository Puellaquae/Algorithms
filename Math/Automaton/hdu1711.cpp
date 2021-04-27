// Number Sqeuence

#include <cstdio>
int next[1000005];
int t[1000005], p[1000005];
int lt, lp;
void getNext() {
    next[0] = -1;
    int i = 0, j = -1;
    while (i < lp) {
        if (j == -1 || p[i] == p[j]) {
            ++i;
            ++j;
            next[i] = j;
        } else
            j = next[j];
    }
}
int KMP() {
    int i = 0;
    int j = 0;
    while (i < lt && j < lp) {
        if (j == -1 || t[i] == p[j]) {
            i++;
            j++;
        } else
            j = next[j];
    }
    if (j == lp)
        return i - j + 1;
    else
        return -1;
}
int main() {
    int k;
    scanf("%d", &k);
    while (k--) {
        scanf("%d%d", &lt, &lp);
        for (int i = 0; i < lt; i++) {
            scanf("%d", t + i);
        }
        for (int i = 0; i < lp; i++) {
            scanf("%d", p + i);
        }
        getNext();
        printf("%d\n", KMP());
    }
}