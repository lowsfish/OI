#include<cstdio>
#include<cstring>
#include<algorithm>
const int MAXN=1000000+5;
typedef long long LL;
int n;
int head[MAXN],next[MAXN<<1],to[MAXN<<1];
int sz[MAXN],fa[MAXN],dep[MAXN];
LL dp[MAXN];
int root=1;
void addEdge(int u,int v)
{
	static int cnt=0;
	to[cnt]=v;
	next[cnt]=head[u];
	head[u]=cnt++;
}
void dfs(int u)
{
	sz[u]=1;
	dp[root]+=dep[u];
	for(int e=head[u];~e;e=next[e]) if(to[e]!=fa[u])
	{
		fa[to[e]]=u;
		dep[to[e]]=dep[u]+1;
		dfs(to[e]);
		sz[u]+=sz[to[e]];
	}
}
void dfs2(int u)
{
	for(int e=head[u];~e;e=next[e]) if(to[e]!=fa[u])
	{
		dp[to[e]]=dp[u]+n-2*sz[to[e]];
		dfs2(to[e]);
	}
}
void input()
{
	memset(head,-1,sizeof(head));
	scanf("%d",&n);
	for(int i=0;i<n-1;++i)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		addEdge(u,v);
		addEdge(v,u);
	}
}
int main()
{
	input();
	dfs(root);
	dfs2(root);
	int ans=0;
	for(int i=1;i<=n;++i) if(dp[i]>dp[ans])
		ans=i;
	printf("%d\n",ans);
	return 0;
}
