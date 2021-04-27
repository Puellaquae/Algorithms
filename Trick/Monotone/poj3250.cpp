// Bad Hair Day

#include <cstdio>
#include <stack>
using namespace std;
const int MAXN = 80050;
int Cow[MAXN];
int main() {
    int N;
    while (~scanf("%d", &N)) {
        for (int i = 0; i < N; i++) {
            scanf("%d", Cow + i);
        }
        stack<int> s;
        long long ans = 0;
        s.push(Cow[0]);
        for (int i = 1; i < N; i++) {
            while (!s.empty() && Cow[i] >= s.top()) {
                s.pop();
            }
            ans += s.size();
            s.push(Cow[i]);
        }
        printf("%lld\n", ans);
    }
}