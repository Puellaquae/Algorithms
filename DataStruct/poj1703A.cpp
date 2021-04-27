#include <iostream>
#include <cstdio>
#include <cstring>
#define MAXN (100000+10)
using namespace std;

int pre[MAXN*2], rank[MAXN*2];

int find(int x){    
    int r = x;
    while(pre[r]!=r){
        r = pre[r];
    }
    int i = x;
    while(pre[i]!=r){
        int gg = pre[i];
        pre[i] = r;
        i = gg;
    }
    return r;
}

void jion(int x, int y){
    int xx = find(x);
    int yy = find(y);
    if(::rank[xx]>::rank[yy]){
        pre[yy] = xx;
    }else{
        pre[xx] = yy;
        if(::rank[xx] == ::rank[yy]){
            ::rank[xx]++;
        }
    }
}

int main(void){
    int t;
    scanf("%d", &t);
    while(t--){
        int n, m;
        scanf("%d%d", &n, &m);
        for(int i=1; i<=2*n; i++){
            pre[i] = i;
            ::rank[i] = 0;
        }
        while(m--){
            char ch[2];
            int x, y;
            scanf("%s%d%d", ch, &x, &y);
            if(ch[0]=='D'){
                jion(x, y+n);
                jion(x+n, y);
            }else{
                if(find(y+n)==find(x)||find(x+n)==find(y)){
                    printf("In different gangs.\n");
                }else if(find(x)==find(y)||find(x+n)==find(y+n)){
                    printf("In the same gang.\n");
                }else{
                    printf("Not sure yet.\n");
                }
            }
        }
    }
    return 0;
}