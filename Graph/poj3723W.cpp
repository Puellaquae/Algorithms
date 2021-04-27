#include <iostream>
#include <cstdio>
#include <fstream>
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <deque>
#include <vector>
#include <queue>
#include <string>
#include <cstring>
#include <map>
#include <stack>
#include <set>
#include <sstream>
#define mod 1000000007
#define eps 1e-6
#define ll long long
#define INF 0x3f3f3f3f
#define MEM(x,y) memset(x,y,sizeof(x))
using namespace std;
int dt[][2]= {{1,0},{-1,0},{0,1},{0,-1},{0,0}};
//typedef pair<int, int> P;
//priority_queue<int, vector<int>, greater<int> > q;
//并查集板子
const int maxn=500010;
int par[maxn];
int rk[maxn];
void init(int n)
{
    for(int i=0;i<n;i++){
        par[i]=i;
        rk[i]=0;
    }
}
int find(int x)
{
    if(par[x]==x)return x;
    else {
        return par[x]=find(par[x]);}
}
void unite(int x,int y)
{
    x=find(x);
    y=find(y);
    if(x==y)return ;

    if(rk[x]<rk[y])
    {
        par[x]=y;
    }
    else par[y]=x;
    if(rk[x]==rk[y])rk[x]++;
}
bool same(int x,int y)
{
    return find(x)==find(y);
}

//最小生成树板子（krusjkal算法）
struct edge{
  int from,to,cost;
};
bool comp(const edge& e1,const edge& e2)
{
    return e1.cost<e2.cost;
}
edge mp[maxn];
int V,E;
int res;
int kruskal()
{
    sort(mp,mp+E,comp);
    init(V);
    res=0;
    for(int i=0;i<E;i++)
    {
        edge s=mp[i];
        if(!same(s.from,s.to)){
            unite(s.from,s.to);
        res+=s.cost;
        }
    }
    return res;
}int a,b,d;
int main(){
   ios::sync_with_stdio(false);
   cin.tie(0);
    int t;
    int n,m,r;
    cin>>t;
    while(t--){
        cin>>n>>m>>r;
        V=n+m;
        E=r;
        for(int i=0;i<r;i++){
            cin>>a>>b>>d;
            mp[i].from=a;
            mp[i].to=b+n;
            mp[i].cost=-d;
        }
        kruskal();
        cout<<10000*(n+m)+res;
    }
    cout.flush();
    system("pause");
}