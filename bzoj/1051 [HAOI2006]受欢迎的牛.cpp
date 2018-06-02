#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#include<stack>
using std::vector;
using std::stack;
using std::min;
typedef vector<int>::iterator vit;
const int MAXN=10000+5;
vector<int> G[MAXN];
stack<int> S;
int scc_cnt,sccno[MAXN],vcnt[MAXN],lowlink[MAXN],pre[MAXN],dfs_clock;
void dfs(int u)
{
	lowlink[u]=pre[u]=++dfs_clock;
	S.push(u);
	for(vit e=G[u].begin();e!=G[u].end();++e)
	{
		if(!pre[*e])
		{
			dfs(*e);
			lowlink[u]=min(lowlink[u],lowlink[*e]);
		}
		else if(!sccno[*e]) lowlink[u]=min(lowlink[u],pre[*e]);
	}
	if(lowlink[u]==pre[u])
	{
		++scc_cnt;
		while(1)
		{
			int x=S.top();S.pop();
			sccno[x]=scc_cnt;
			++vcnt[scc_cnt];
			if(x==u) break;
		}
	}
}
void find_scc(int n)
{
	scc_cnt=0;
	memset(pre,0,sizeof pre);
	for(int i=1;i<=n;++i) if(!pre[i])
		dfs(i);
}
int n,m;
bool out0[MAXN];
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=0;i<m;++i)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		G[u].push_back(v);
	}
	find_scc(n);
	memset(out0,1,sizeof out0);
	for(int i=1;i<=n;++i)
		for(vit e=G[i].begin();e!=G[i].end();++e)
			if(sccno[i]!=sccno[*e])  out0[sccno[i]]=0;
	int cnt=0,t;
	for(int i=1;i<=scc_cnt;++i) if(out0[i])
		++cnt,t=i;
	if(cnt>1) puts("0");
	else printf("%d\n",vcnt[t]);
	return 0;
}
