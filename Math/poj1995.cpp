// Raising Modulo Numbers

#include <iostream>
using namespace std;
typedef long long int64;
int64 mpow(int64 x, int64 n, int64 mod) {
    int64 res = 1;
    while (n > 0) {
        if (n & 1)
            res = res * x % mod;
        x = x * x % mod;
        n >>= 1;
    }
    return res;
}

int main(){
    ios::sync_with_stdio(false);
    cout.tie(NULL);
    cin.tie(NULL);
    int T;
    cin>>T;
    while(T--){
        int H,M;
        cin>>M>>H;
        int64 res=0;
        for(int i=0;i<H;i++){
            int64 a,b;
            cin>>a>>b;
            res=(res+mpow(a,b,M))%M;
        }
        cout<<res<<'\n';
    }
}