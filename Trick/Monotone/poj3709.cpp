// K-Anonymous Sequence

#include <algorithm>
#include <iostream>
#define MAX_N 500050
typedef long long i64;
int n, k;
i64 a[MAX_N + 1];
i64 dp[MAX_N + 1];
i64 S[MAX_N + 1];
int deq[MAX_N];
#define CHECK(i) i64 a##i = -a[f##i], b##i = dp[f##i] - S[f##i] + a[f##i] * f##i
using namespace std;

i64 f(int j, int x) { return -a[j] * x + dp[j] - S[j] + a[j] * j; }
bool check(int f1, int f2, int f3) {
    CHECK(1);
    CHECK(2);
    CHECK(3);
    return (a2 - a1) * (b3 - b2) >= (b2 - b1) * (a3 - a2);
}
void solve(){
    for(int i=0;i<n;i++){
        S[i+1]=S[i]+a[i];
    }
    int s=0,t=1;
    deq[0]=0;
    dp[0]=0;
    for(int i=k;i<=n;i++){
        if(i-k>=k){
            while(s+1<t&&check(deq[t-2],deq[t-1],i-k))t--;
            deq[t++]=i-k;
        }
        while(s+1<t&&f(deq[s],i)>=f(deq[s+1],i))s++;
        dp[i]=S[i]+f(deq[s],i);
    }
    printf("%lld\n",dp[n]);
}
int main() {
    int t;
    scanf("%d",&t);
    while(t--){
        scanf("%d%d",&n,&k);
        for(int i=0;i<n;i++){
            scanf("%lld",a+i);
        }
        solve();
    }
}