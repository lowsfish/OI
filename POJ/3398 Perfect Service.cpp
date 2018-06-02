#include<cstdio>
#include<algorithm>
#include<cstring>
#include<vector>
#define pb push_back
const int MAXN=10000+5;
const int INF=1<<28;
int n;
int p[MAXN];
std::vector<int> G[MAXN];
std::vector<int> sons[MAXN];
int dp[MAXN][3];
void dfs(int u,int fa)
{
	p[u]=fa;
	for(int i=0;i<G[u].size();++i)
	{
		int v=G[u][i];
		if(v!=fa) sons[u].pb(v),dfs(v,u);
	}
}
int src(int u,int flag)
{
	if(dp[u][flag]>=0) return dp[u][flag];
	int ans=0;
	if(flag==0)
	{
		for(int i=0;i<sons[u].size();++i)
		{
			int v=sons[u][i];
			ans+=std::min(src(v,0),src(v,1));
		}
		ans+=1;
	}
	else if(flag==1)
	{
		for(int i=0;i<sons[u].size();++i)
			ans+=src(sons[u][i],2);
	}
	else
	{
		ans=INF;
		int t=src(u,1);
		for(int i=0;i<sons[u].size();++i)
		{
			int v=sons[u][i];
			ans=std::min(ans,t-src(v,2)+src(v,0));
		}
	}
	return dp[u][flag]=ans;
}
void init()
{
	for(int i=1;i<=n;++i)
	{
		G[i].clear();
		sons[i].clear();
	}
	memset(dp,-1,sizeof(dp));
}
int main()
{
	//freopen("1.in","r",stdin);
	while(scanf("%d",&n)!=EOF)
	{
		if(!n) printf("0\n");
		else
		{
			init();
			for(int i=1;i<n;++i)
			{
				int u,v;
				scanf("%d%d",&u,&v);
				G[u].pb(v);
				G[v].pb(u);
			}
			dfs(1,-1);
			printf("%d\n",std::min(src(1,0),src(1,2)));
		}
		scanf("%d",&n);
		if(n==-1) break;
	}
	return 0;
}
