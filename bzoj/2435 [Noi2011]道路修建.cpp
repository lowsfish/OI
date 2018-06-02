#include<cstdio>
#include<vector>
#include<algorithm>
typedef long long LL;
const int MAXN=1000000+5;
using std::vector;
struct Edge{
	int v,c;
	Edge(int v,int c):v(v),c(c) {}
};
typedef vector<Edge>::iterator vit;
vector<Edge> G[MAXN];
int sz[MAXN],fa[MAXN];
int n;
LL ans;
void dfs(int u)
{
	sz[u]=1;
	for(vit e=G[u].begin();e!=G[u].end();++e) if(e->v!=fa[u])
	{
		fa[e->v]=u;
		dfs(e->v);
		sz[u]+=sz[e->v];
		ans+=(LL)std::abs(n-2*sz[e->v])*e->c;
	}
}
int main()
{
	scanf("%d",&n);
	for(int i=0;i<n-1;++i)
	{
		int u,v,c;
		scanf("%d%d%d",&u,&v,&c);
		G[u].push_back(Edge(v,c));
		G[v].push_back(Edge(u,c));
	}
	dfs(1);
	printf("%lld\n",ans);
	return 0;
}
