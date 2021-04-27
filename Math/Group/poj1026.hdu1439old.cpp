// Cipher

#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>
using namespace std;
int key[255];
void solve(int n) {
    for (int i = 1, t; i <= n; i++) {
        scanf("%d", &t);
        key[t] = i;
    }
    int m;
    char str[255];
    while (~scanf("%d", &m) && m) {
        memset(str, ' ', sizeof(str));
        gets(str);
        for (int i = 1; i <= n; i++) {
            int pos = i;
            for (int j = 0; j < m; j++) {
                pos = key[pos];
            }
            printf("%c", str[pos]);
        }
        printf("\n");
    }
}
int main() {
    int n;
    while (~scanf("%d", &n) && n) {
        solve(n);
        printf("\n");
    }
}