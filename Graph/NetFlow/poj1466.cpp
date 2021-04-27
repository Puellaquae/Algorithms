// Girls And Boys

#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;
const int MAX_V = 1000;
int V;
vector<int>G[MAX_V];
int match[MAX_V];
bool used[MAX_V];
void addEdge(int u,int v){
    G[u].push_back(v);
    G[v].push_back(u);
}
bool dfs(int v){
    used[v]=true;
    for(int i=0;i<G[v].size();i++){
        int u=G[v][i],w=match[u];
        if(w<0||!used[w]&&dfs(w)){
            match[v]=u;
            match[u]=v;
            return true;
        }
    }
    return false;
}
int bitch(){
    int res=0;
    memset(match,-1,sizeof(match));
    for(int v=0;v<V;v++){
        if(match[v]<0){
            memset(used,0,sizeof(used));
            if(dfs(v)){
                res++;
            }
        }
    }
    return res;
}
int N;
void solve() {
    V=N;
    for(int i=0;i<V;i++){
        G[i].clear();
    }
    for(int i=0,j,m;i<N;i++){
        scanf("%d: (%d)",&j,&m);
        for(int k=0,id;k<m;k++){
            scanf("%d",&id);
            G[j].push_back(id);
        }
    }
    
    printf("%d\n",N-bitch());
}
int main() {
    while (~scanf("%d", &N)) {
        solve();
    }
}