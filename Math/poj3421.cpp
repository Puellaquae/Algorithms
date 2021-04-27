// X-factor Chains

#include <iostream>
#include <map>
#include <vector>
using namespace std;
typedef long long int64;
int main() {
    ios::sync_with_stdio(false);
    cout.tie(NULL);
    cin.tie(NULL);
    int64 x;
    while (cin >> x) {
        map<int,int> Fac;int64 facs=0;
        for (int64 i = 2; i * i <= x; i++) {
            while (x % i == 0) {
                Fac[i]++;facs++;
                x /= i;
            }
        }
        if(x>1){
            Fac[x]++;facs++;
        }
        int64 ans=1;
        for(int64 i=2;i<=facs;i++){
            ans*=i;
        }
        for(map<int,int>::iterator it=Fac.begin();it!=Fac.end();it++){
            for(int64 i=2;i<=it->second;i++){
                ans/=i;
            }
        }
        cout<<facs<<" "<<ans<<'\n';
    }
}