#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<queue>
using namespace std;
const int MAXM=50000+10;
const int MAXN=10000+10;
bool vis[MAXN];
int pa[MAXN],anc[MAXN][17],mincost[MAXN][17];	//pa是并查集上的父节点
				//anc[i][j]代表结点i向上走2^j步走到的结点。-1代表不存在
int fa[MAXN],cost[MAXN];//树上的父节点,cost[i]代表该结点到它父亲节点的权值
int n,m,q;
int depth[MAXN];
const int INF=1<<27;
struct edge{
	int u,v,cost;
	edge(int u=0,int v=0,int cost=0):u(u),v(v),cost(cost) {}
	bool operator<(const edge &a)const
	{
		return cost<a.cost;
	}
}es[MAXM];
vector<edge> G[MAXN];

//unite-find set
inline int find(int x)
{
	return pa[x]==x?x:pa[x]=find(pa[x]);
}

void init()
{
     for(int i=0;i<=n;++i) pa[i]=i;     
}

void unite(int x,int y)
{
	x=find(x);
	y=find(y);
	if(x==y) return;
	pa[x]=y;
}

bool same(int x,int y)
{
	return find(x)==find(y);
}

//kruskal
void kruskal()
{
	sort(es,es+m);
	for(int i=m-1;i>=0;--i)
	{
		if(!same(es[i].u,es[i].v))
		{
			unite(es[i].u,es[i].v);
			G[es[i].u].push_back(edge(0,es[i].v,es[i].cost));
			G[es[i].v].push_back(edge(0,es[i].u,es[i].cost));//实际只用到后面两个参数，所以第一个参数值任意
		}
	}
}

void dfs(int v,int p,int d,int val)
{
	fa[v]=p;
	depth[v]=d;
	cost[v]=val;
	for(int i=0;i<G[v].size();++i)
	{
		edge e=G[v][i];
		if(e.v!=p)
		{
			dfs(e.v,v,d+1,e.cost);
		}
	}
}

void LCA_init()		//实际上没求LCA。。
{
	for(int i=1;i<=n;++i)
	{
		anc[i][0]=fa[i];
		mincost[i][0]=cost[i];
		for(int j=1;(1<<j)<=n;++j) anc[i][j]=-1;
	}
	for(int j=1;(1<<j)<n;++j)
		for(int i=1;i<=n;++i)
		{
			if(anc[i][j-1]!=-1)
			{
				int a=anc[i][j-1];
				anc[i][j]=anc[a][j-1];
				mincost[i][j]=min(mincost[i][j-1],mincost[a][j-1]);
			}
		}
}

int query(int p,int q)
{
	int log,i;
	if(depth[p]<depth[q]) swap(p,q);
	for(log=1;(1<<log)<=depth[p];++log);--log;
	int ans=INF;
	for(int i=log;i>=0;--i)
	{
		if(depth[p]-(1<<i)>=depth[q])
		{
			ans=min(ans,mincost[p][i]);
			p=anc[p][i];
		}
	}
	if(p==q) return ans;
	for(int i=log;i>=0;--i)
	{
		if(anc[p][i]!=-1 && anc[p][i]!=anc[q][i])
		{
			ans=min(ans,min(mincost[p][i],mincost[q][i]));
			p=anc[p][i];
			q=anc[q][i];
		}
	}
	ans=min(ans,min(cost[p],cost[q]));
	return ans;
}
int main()
{
	//freopen("1.in","r",stdin);
	scanf("%d%d",&n,&m);
	init();
	for(int i=0;i<m;++i)
	{
		int a,b,c;
		scanf("%d%d%d",&a,&b,&c);
		es[i]=edge(a,b,c);
	}
	kruskal();
	int q;
	scanf("%d",&q);
	for(int i=1;i<=n;++i)
	{
		if(!fa[i]) 
		{
			dfs(i,-1,1,INF);
		}
	}
	LCA_init();
	for(int i=0;i<q;++i)
	{
		int s,t;
		scanf("%d%d",&s,&t);
		if(!same(s,t)) printf("-1\n");
		else printf("%d\n",query(s,t));
	}
	return 0;
}
