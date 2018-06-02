#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
const int INF=~0U>>1;
const int MAXN=10000+10;
struct Edge{
	int u,v,cost;
	Edge() {}
	Edge(int u,int v,int cost):u(u),v(v),cost(cost) {}
}edges[MAXN<<1];
//std::vector<Edge> G[MAXN];
int son[MAXN],dep[MAXN],w[MAXN],fa[MAXN],top[MAXN],sz[MAXN];
int head[MAXN<<1],next[MAXN<<1];
int dfs_clock;
int n;
inline void addedge(int u,int v,int cost,int edge)
{
	edges[edge]=Edge(u,v,cost);
	next[edge]=head[u];
	head[u]=edge;
}
void dfs(int u)
{
	sz[u]=1;son[u]=-1;
	for(int i=head[u];~i;i=next[i]) if(edges[i].v!=fa[u])
	{
		int v=edges[i].v;
		fa[v]=u;
		dep[v]=dep[u]+1;
		dfs(v);
		if(son[u]==-1 || sz[v]>sz[son[u]]) son[u]=v;
		sz[u]+=sz[v];
	}
}
void dfs2(int u,int tp)
{
	w[u]=++dfs_clock;top[u]=tp;
	if(~son[u]) dfs2(son[u],tp);
	for(int i=head[u];~i;i=next[i]) if(edges[i].v!=fa[u] && edges[i].v!=son[u])
		dfs2(edges[i].v,edges[i].v);
}
int maxv[(1<<14)+10];
int totn;
void maintain(int o)
{
	maxv[o]=std::max(maxv[o<<1],maxv[o<<1|1]);
}
void build(int o,int l,int r)
{
	if(l==r) return;
	int m=l+r>>1;
	build(o<<1,l,m);
	build(o<<1|1,m+1,r);
	maxv[o]=std::max(maxv[o<<1],maxv[o<<1|1]);
}
int ask(int o,int l,int r,int x1,int x2)
{
	if(r<x1 || l>x2) return -1;
	if(l>=x1 && r<=x2) return maxv[o];
	int m=l+r>>1;
	return std::max(ask(o<<1,l,m,x1,x2),ask(o<<1|1,m+1,r,x1,x2));
}
void update(int o,int l,int r,int x,int a)
{
	if(l==r) maxv[o]=a;
	else
	{
		int m=l+r>>1;
		if(x<=m) update(o<<1,l,m,x,a);
		else update(o<<1|1,m+1,r,x,a);
		maintain(o);
	}
}
void init()
{
	//memset(sz,0,sizeof(sz));
	//memset(maxv,-1,sizeof(maxv));
	memset(head,-1,sizeof(head));
	for(int i=0;i<=n;++i) sz[i]=0;
	dep[0]=0;
	dfs_clock=0;
	fa[0]=-1;
	int k=0;
	while((1<<k)<n) ++k;
	totn=1<<k;
	for(int i=0;i<=(totn<<1);++i) maxv[i]=-1;
}
int query(int u,int v)
{
	int f1=top[u],f2=top[v],ans=-1;
	while(f1!=f2)
	{
		if(dep[f1]<dep[f2])
			std::swap(f1,f2),std::swap(u,v);
		ans=std::max(ans,ask(1,1,totn,w[f1],w[u]));
		u=fa[f1];f1=top[u];
	}
	if(u==v) return ans;
	if(dep[u]<dep[v]) std::swap(u,v);
	return std::max(ans,ask(1,1,totn,w[son[v]],w[u]));
}
int main()
{
	//freopen("1.in","r",stdin);
	int T;
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&n);
		init();
		for(int i=0;i<n-1;++i)
		{
			int u,v,cost;
			scanf("%d%d%d",&u,&v,&cost);
			--u;--v;
			addedge(u,v,cost,i<<1);
			addedge(v,u,cost,i<<1|1);
		}
		dfs(0);
		dfs2(0,0);
		for(int i=0;i<n-1;++i)
		{
			int u=edges[i<<1].u,v=edges[i<<1].v;
			if(dep[u]>dep[v]) std::swap(u,v);
			update(1,1,totn,w[v],edges[i<<1].cost);
		}
		char s[10];
		while(scanf("%s",s)==1 && s[0]!='D')
		{
			if(s[0]=='Q')
			{
				int u,v;
				scanf("%d%d",&u,&v);
				--u;--v;
				printf("%d\n",query(u,v));
			}
			else
			{
				int x,a;
				scanf("%d%d",&x,&a);
				--x;
				int u=edges[x<<1].u,v=edges[x<<1].v;
				if(dep[u]>dep[v]) std::swap(u,v);
				update(1,1,totn,w[v],a);
			}
		}
	}
	return 0;
}
