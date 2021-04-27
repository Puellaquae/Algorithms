// Prime Number
#include <iostream>
#include <vector>
using namespace std;
vector<bool> Primes(1000005, true);

int main() {
    Primes[1] = false;
    for (int i = 2; i < (int)Primes.size(); i++) {
        if (Primes[i]==false)
            continue;
        for (int k = 2; i * k < (int)Primes.size(); k++) {
            Primes[i * k] = false;
        }
    }
    int x;
    while(cin>>x){
        int ans=0;
        for(int i=2;i<=x;i++){
            if(Primes[i]){
                ans++;
            }
        }
        cout<<ans<<endl;
    }
}