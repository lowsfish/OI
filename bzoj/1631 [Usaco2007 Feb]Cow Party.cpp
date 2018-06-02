#include<cstdio>
#include<vector>
#include<algorithm>
#include<cstring>
#include<queue>
const int MAXN=1000+5;
const int INF=~0U>>1;
int n,m,p;
struct Edge{
	int v,c;
	Edge(int v,int c):v(v),c(c) {}
};
std::vector<Edge> G[2][MAXN];
typedef std::vector<Edge>::iterator vit;
int d[2][MAXN];
bool inq[MAXN];
void spfa(bool flag,int s)
{
	std::fill(d[flag]+1,d[flag]+n+1,INF);
	memset(inq,0,sizeof(inq));
	std::queue<int> que;
	que.push(s);
	d[flag][s]=0;inq[s]=1;
	while(!que.empty())
	{
		int u=que.front();que.pop();
		inq[u]=0;
		for(vit e=G[flag][u].begin();e!=G[flag][u].end();++e) if(d[flag][e->v] > d[flag][u]+e->c)
		{
			d[flag][e->v]=d[flag][u]+e->c;
			if(!inq[e->v]) que.push(e->v),inq[e->v]=1;
		}
	}
}
int main()
{
	scanf("%d%d%d",&n,&m,&p);
	while(m--)
	{
		int u,v,c;
		scanf("%d%d%d",&u,&v,&c);
		G[0][u].push_back(Edge(v,c));
		G[1][v].push_back(Edge(u,c));
	}
	spfa(0,p);
	spfa(1,p);
	int ans=0;
	for(int i=1;i<=n;++i)if(i!=p) ans=std::max(ans,d[0][i]+d[1][i]);
	printf("%d\n",ans);
	return 0;
}
