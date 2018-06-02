#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
const int MAXSZ=100001;
using namespace std;
int pa[MAXSZ];
typedef long long LL;
int n,m;
struct edge{
       int u,v;
       LL cost;
       edge() {}
       edge(int u,int v,LL cost):u(u),v(v),cost(cost) {}
       }es[MAXSZ];

bool cmp(const edge &a,const edge &b)
{
     return a.cost<b.cost;
     }
void init()
{
     for(int i=0;i<=n;++i)
     { 
             pa[i]=i; 
     }
}
int find(int x)
{
    return pa[x]==x?x:pa[x]=find(pa[x]);
}

void unite(int x,int y)
{
     x=find(x);
     y=find(y);
     if(x!=y) pa[x]=y;
     }
     
bool same(int x,int y)
{
     return find(x)==find(y);
     }

LL kruskal()
{
    init();
    sort(es,es+m,cmp);
    LL ans=0;
    for(int i=0;i<m;++i)
    {
            edge e=es[i];
            if(!same(e.u,e.v))
            {
                ans+=e.cost;
                unite(e.u,e.v);        
            }
    }
    return ans;
}

int main()
{
    cin>>n>>m;
    if(n>m) 
    {
              cout<<"-1";
              return 0;
              }
    for(int i=0;i<m;++i)
    {
            int u,v;
            LL cost;
            cin>>u>>v>>cost;
            es[i]=edge(u,v,cost);
    }
    cout<<kruskal();
    return 0;
    }
