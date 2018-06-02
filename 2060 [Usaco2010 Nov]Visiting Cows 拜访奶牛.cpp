#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
const int MAXN=50000+5;
int fa[MAXN];
int n;
std::vector<int> G[MAXN];
typedef std::vector<int>::iterator vit;
void input()
{
	scanf("%d",&n);
	for(int i=0;i<n-1;++i)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		G[u].push_back(v);
		G[v].push_back(u);
	}
}
int root;
void dfs(int u)
{
	for(vit e=G[u].begin();e!=G[u].end();++e) if(*e!=fa[u])
	{
		fa[*e]=u;
		dfs(*e);
	}
}
int dp[MAXN][2];
int src(int u,bool k)
{
	int& ans=dp[u][k];
	if(ans>=0) return ans;
	ans=0;
	if(k)
	{
		ans++;
		for(vit e=G[u].begin();e!=G[u].end();++e) if(*e!=fa[u])
			ans+=src(*e,0);
	}
	else
	{
		for(vit e=G[u].begin();e!=G[u].end();++e) if(*e!=fa[u])
			ans+=std::max(src(*e,1),src(*e,0));
	}
	return ans;
}
int main()
{
	//freopen("1.in","r",stdin);
	input();
	root=1;
	dfs(root);
	memset(dp,-1,sizeof dp);
	printf("%d\n",std::max(src(root,0),src(root,1)));
	return 0;
}
