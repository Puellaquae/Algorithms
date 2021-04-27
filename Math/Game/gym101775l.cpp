//SOS

#include <cstdio>
int main() {
    int T,n;
    scanf("%d", &T);
    for (int kase = 1; kase <= T; kase++) {
        scanf("%d", &n);
        printf("Case #%d: ", kase);
        if (n < 7)
            puts("Draw");
        else if (n >= 7 && n < 16) {
            puts(n % 2 ? "Panda" : "Draw");
        } else {
            puts(n % 2 ? "Panda" : "Sheep");
        }
    }
    return 0;
}