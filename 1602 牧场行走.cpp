#include<cstdio>
#include<vector>
#include<algorithm>
const int MAXN=1000+10;
int n,q;
int dis[MAXN],fa[MAXN],dep[MAXN];
int step[MAXN][10];
struct Edge{
	int v,c;
	Edge(int v,int c):v(v),c(c) {}
};
std::vector<Edge> G[MAXN];
typedef std::vector<Edge>::iterator it;
void dfs(int u)
{
	for(it e=G[u].begin();e!=G[u].end();++e) if(e->v!=fa[u])
	{
		fa[e->v]=u;
		dep[e->v]=dep[u]+1;
		dis[e->v]=dis[u]+e->c;
		dfs(e->v);
	}
}
void LCA_init()
{
	for(int i=1;i<=n;++i) step[i][0]=fa[i];
	for(int i=1;(1<<i)<n;++i)
		for(int j=1;j<=n;++j)
		{
			step[j][i]=step[step[j][i-1]][i-1];
		}
}
int LCA(int u,int v)
{
	if(dep[u]<dep[v]) std::swap(u,v);
	int log;
	for(log=0;(1<<log)<n;++log);--log;
	for(int i=log;i>=0;--i) if(dep[u]-(1<<i)>=dep[v])
		u=step[u][i];
	for(int i=log;i>=0;--i) if(step[u][i]!=step[v][i])
		u=step[u][i],v=step[v][i];
	if(u==v) return u;
	else return fa[u];
}
int main()
{
	freopen("1.in","r",stdin);
	scanf("%d%d",&n,&q);
	for(int i=0;i<n-1;++i)
	{
		int u,v,c;
		scanf("%d%d%d",&u,&v,&c);
		G[u].push_back(Edge(v,c));
		G[v].push_back(Edge(u,c));
	}
	dfs(1);
	LCA_init();
	while(q--)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		int lca=LCA(u,v);
		printf("%d\n",dis[u]+dis[v]-(dis[lca]<<1));
	}
	return 0;
}
