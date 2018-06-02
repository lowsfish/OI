#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#include<stack>
using namespace std;
const int MAXN=1000+10;
int sccno[MAXN],pre[MAXN],lowlink[MAXN],dfs_clock,scc_cnt;
vector<int> G[MAXN];
bool GC[MAXN][MAXN];
stack<int> S;
void dfs(int u)
{
	lowlink[u]=pre[u]=++dfs_clock;
	S.push(u);
	for(int i=0;i<G[u].size();++i)
	{
		int v=G[u][i];
		if(!pre[v])
		{
			dfs(v);
			lowlink[u]=min(lowlink[u],lowlink[v]);
		}
		else if(!sccno[v]) lowlink[u]=min(lowlink[u],pre[v]);
	}
	if(lowlink[u]==pre[u])
	{
		++scc_cnt;
		for(;;)
		{
			int x=S.top();S.pop();
			sccno[x]=scc_cnt;
			if(x==u) break;
		}
	}
}
void find_scc(int n)
{
	for(int i=0;i<n;++i) 
		if(!pre[i]) dfs(i);
}
int n,m;
int in[MAXN];
int maxd=-1;
void dfs2(int u,int cur)
{
	maxd=max(maxd,cur);
	for(int i=1;i<=scc_cnt;++i)
	{
		if(GC[u][i]) dfs2(i,cur+1);
	}
}
void init()
{
	maxd=-1;
	dfs_clock=scc_cnt=0;
	memset(GC,0,sizeof(GC));
	for(int i=0;i<=n;++i)
	{
		G[i].clear();
		in[i]=lowlink[i]=pre[i]=sccno[i]=0;
	}
}
int main()
{
	//freopen("1.in","r",stdin);
	int T;
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d",&n,&m);
		init();
		while(m--)
		{
			int u,v;
			scanf("%d%d",&u,&v);
			--u;--v;
			G[u].push_back(v);
		}
		find_scc(n);
		for(int u=0;u<n;++u)
		{
			for(int i=0;i<G[u].size();++i)
			{
				int v=G[u][i];
				if(sccno[u]!=sccno[v])
				{
					if(!GC[sccno[u]][sccno[v]]) in[sccno[v]]++;
					GC[sccno[u]][sccno[v]]=1;
				}
			}
		}
		for(int i=1;i<=scc_cnt;++i) if(!in[i])
		{
			dfs2(i,1);
			break;
		}
		if(maxd==scc_cnt) printf("Yes\n");
		else printf("No\n");
	}
	return 0;
}
