#include<cstdio>
#include<vector>
#include<algorithm>
#include<queue>
const int MAXM=20+5;
const int MAXN=100+5;
const int INF=~0U>>1;
struct Edge{
	int v,c;
	Edge(int v,int c):v(v),c(c) {}
};
std::vector<Edge> G[MAXM];
typedef std::vector<Edge>::iterator vit;
bool forbid[MAXM][MAXN][MAXN];
int n,m,k,e;
void input()
{
	scanf("%d%d%d%d",&n,&m,&k,&e);
	while(e--)
	{
		int u,v,c;
		scanf("%d%d%d",&u,&v,&c);
		G[u].push_back(Edge(v,c));
		G[v].push_back(Edge(u,c));
	}
	int d;
	scanf("%d",&d);
	while(d--)
	{
		int p,a,b;
		scanf("%d%d%d",&p,&a,&b);
		for(int i=1;i<=b;++i)
			for(int j=std::max(i,a);j<=n;++j)
				forbid[p][i][j]=1;
	}
}
int dist[MAXN][MAXN];
bool inq[MAXM];
int d[MAXM];
int spfa(int s,int t,int a,int b)
{
	for(int i=1;i<=m;++i) d[i]=i==s?0:INF,inq[i]=0;
	std::queue<int> que;
	que.push(s);inq[s]=1;
	while(!que.empty())
	{
		int u=que.front();que.pop();
		inq[u]=0;
		for(vit e=G[u].begin();e!=G[u].end();++e)
			if(d[e->v]>d[u]+e->c && !forbid[e->v][a][b])
			{
				d[e->v]=d[u]+e->c;
				if(!inq[e->v]) que.push(e->v),inq[e->v]=1;
			}
	}
	return d[t];
}
int dp[MAXN];
void work()
{
	for(int i=1;i<=n;++i)
		for(int j=i;j<=n;++j)
			dist[i][j]=spfa(1,m,i,j);
	for(int i=1;i<=n;++i)
	{
		if(dist[1][i]!=INF) dp[i]=dist[1][i]*i;
		else dp[i]=INF;
		for(int j=1;j<i;++j) if(dist[j+1][i]!=INF)
			dp[i]=std::min(dp[i],dp[j]+k+dist[j+1][i]*(i-j));
	}
	printf("%d\n",dp[n]);
}
int main()
{
	freopen("1.in","r",stdin);
	input();
	work();
	return 0;
}
