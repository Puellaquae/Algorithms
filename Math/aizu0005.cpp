//GCD & LCM
#include<iostream>

typedef long long i64;

i64 GCD(i64 a,i64 b){
    if(b==0){
        return a;
    }else{
        return GCD(b,a%b);
    }
}

int main(){
    i64 a,b;
    while(std::cin>>a>>b){
        i64 gcd=GCD(a,b);
        std::cout<<gcd<<" "<<a/gcd*b<<'\n';
    }
    return 0;
}