#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#include<queue>
const int MAXN=100000+5;
const int INF=~0U>>1;
struct Edge{
	int v,c;
	Edge(int _v,int _c):v(_v),c(_c) {}
};
int gcd(int a,int b)
{
	return b?gcd(b,a%b):a;
}
using std::vector;
typedef vector<Edge>::iterator vit;
vector<Edge> G[MAXN];
int n,m;
int mark[MAXN];
bool vis[MAXN];
int maxMark,minMark,len;
void dfs(int u)
{
	vis[u]=1;
	maxMark=std::max(maxMark,mark[u]);
	minMark=std::min(minMark,mark[u]);
	for(vit e=G[u].begin();e!=G[u].end();++e)
		if(!vis[e->v])
		{
			mark[e->v]=mark[u]+e->c;
			dfs(e->v);
		}
		else
		{
			int t=mark[u]+e->c-mark[e->v];
			if(!t) continue;
			if(t<0) t*=-1;
			if(!len) len=t;
			else len=gcd(len,t);
		}
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=0;i<m;++i)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		G[u].push_back(Edge(v,1));
		G[v].push_back(Edge(u,-1));
	}
	int ans=0;
	for(int i=1;i<=n;++i) if(!vis[i])
	{
		maxMark=-INF;
		minMark=INF;
		dfs(i);
		ans+=maxMark-minMark+1;
	}
	if(len)
	{
		if(len<3) puts("-1 -1");
		else
		{
			printf("%d ",len);
			for(int i=3;i<=len;++i) if(len%i==0)
			{
				printf("%d\n",i);
				break;
			}
		}
	}
	else
	{
		if(ans<3) puts("-1 -1");
		else printf("%d 3\n",ans);
	}
	return 0;
}
