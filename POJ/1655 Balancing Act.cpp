#include<cstdio>
#include<vector>
#include<algorithm>
#include<cstring>
const int MAXN=20000+5;
const int INF=1<<28;
std::vector<int> G[MAXN];
int maxs[MAXN],s[MAXN];
int T,n;
void init()
{
	for(int i=0;i<n;++i)
	{
		G[i].clear();
		maxs[i]=0;
		s[i]=0;
	}
}
void dfs(int u,int fa)
{
	s[u]=1;
	for(int i=0;i<G[u].size();++i)
	{
		int v=G[u][i];
		if(v!=fa)
		{
			dfs(v,u);
			s[u]+=s[v];
			maxs[u]=std::max(maxs[u],s[v]);
		}
	}
}
int main()
{
	//freopen("1.in","r",stdin);
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&n);
		init();
		for(int i=1;i<n;++i)
		{
			int u,v;
			scanf("%d%d",&u,&v);
			--u;--v;
			G[u].push_back(v);
			G[v].push_back(u);
		}
		dfs(0,-1);
		int ans=INF,pla;
		for(int i=0;i<n;++i)
		{
			int t=std::max(maxs[i],n-s[i]);
			if(t<ans) ans=t,pla=i+1;
		}
		printf("%d %d\n",pla,ans);
	}
	return 0;
}
