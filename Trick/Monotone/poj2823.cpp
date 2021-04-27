// Sliding Window

#include <cstdio>
using namespace std;
const int MAXN = 1000000 + 30;
int num[MAXN], bmin[MAXN], bmax[MAXN];
int deq[MAXN];
int front, back;
int main() {
    int n, k;
    scanf("%d%d", &n, &k);
    for (int i = 0; i < n; i++) {
        scanf("%d", num + i);
    }
    front = 0;
    back = 0;
    for (int i = 0; i < n; i++) {
        while (front < back && num[deq[back - 1]] >= num[i])
            back--;
        deq[back++] = i;
        if (i - k + 1 >= 0) {
            bmin[i - k + 1] = num[deq[front]];
            if (deq[front] == i - k + 1) {
                front++;
            }
        }
    }
    front = 0;
    back = 0;
    for (int i = 0; i < n; i++) {
        while (front < back && num[deq[back - 1]] <= num[i])
            back--;
        deq[back++] = i;
        if (i - k + 1 >= 0) {
            bmax[i - k + 1] = num[deq[front]];
            if (deq[front] == i - k + 1) {
                front++;
            }
        }
    }
    for (int i = 0; i <= n - k; i++)
        printf("%d ", bmin[i]);
    printf("\n");
    for (int i = 0; i <= n - k; i++)
        printf("%d ", bmax[i]);
    printf("\n");
}