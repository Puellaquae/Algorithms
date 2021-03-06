// Dual Core CPU

#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

const int MAX_V=50000;
const int INF=0x7fffffff;
struct edge{
    int to,cap,rev;
};
vector<edge> G[MAX_V];
int level[MAX_V];
int iter[MAX_V];
void addEdge(int from,int to,int cap){
    G[from].push_back((edge){to,cap,G[to].size()});
    G[to].push_back((edge){from,0,G[from].size()-1});
}
void bfs(int s){
    memset(level,-1,sizeof(level));
    queue<int> que;
    level[s]=0;
    que.push(s);
    while(!que.empty()){
        int v=que.front();que.pop();
        for(int i=0;i<(int)G[v].size();i++){
            edge& e=G[v][i];
            if(e.cap>0&&level[e.to]<0){
                level[e.to]=level[v]+1;
                que.push(e.to);
            }
        }
    }
}
int dfs(int v,int t,int f){
    if(v==t)return f;
    for(int&i=iter[v];i<(int)G[v].size();i++){
        edge&e=G[v][i];
        if(e.cap>0&&level[v]<level[e.to]){
            int d=dfs(e.to,t,min(f,e.cap));
            if(d>0){
                e.cap-=d;
                G[e.to][e.rev].cap+=d;
                return d;
            }
        }
    }
    return 0;
}
int maxFlow(int s,int t){
    int flow=0;
    for(;;){
        bfs(s);
        if(level[t]<0)return flow;
        memset(iter,0,sizeof(iter));
        int f;
        while((f=dfs(s,t,INF))>0){
            flow+=f;
        }
    }
}

int N,M;
const int MAX_N=20000+5;
const int MAX_M=200000+5;
int A[MAX_N],B[MAX_N];
int a[MAX_M],b[MAX_M],w[MAX_M];
void solve(){
    int s=N,t=s+1;
    for(int i=0;i<N;i++){
        addEdge(i,t,A[i]);
        addEdge(s,i,B[i]);
    }
    for(int i=0;i<M;i++){
        addEdge(a[i]-1,b[i]-1,w[i]);
        addEdge(b[i]-1,a[i]-1,w[i]);
    }
    printf("%d\n",maxFlow(s,t));
}
int main(){
    scanf("%d%d",&N,&M);
    for(int i=0;i<N;i++){
        scanf("%d%d",A+i,B+i);
    }
    for(int i=0;i<M;i++){
        scanf("%d%d%d",a+i,b+i,w+i);
    }
    solve();
}