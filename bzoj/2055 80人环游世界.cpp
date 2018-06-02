#include<cstdio>
#include<cstring>
#include<queue>
#include<vector>
#include<algorithm>
const int MAXN=200+5;
const int INF=~0U>>1;
struct Edge{
	int from,to,cap,flow,cost;
	Edge(int u,int v,int c,int f,int co):from(u),to(v),cap(c),flow(f),cost(co) {}
};
using std::vector;
using std::min;
typedef vector<int>::iterator vit;
struct MCMF{
	int n,m,s,t;
	vector<Edge> edges;
	vector<int> G[MAXN];
	bool inq[MAXN];
	int a[MAXN],p[MAXN],d[MAXN];
	inline void addEdge(int from,int to,int cap,int cost)
	{
		edges.push_back(Edge(from,to,cap,0,cost));
		edges.push_back(Edge(to,from,0,0,-cost));
		m=edges.size();
		G[from].push_back(m-2);
		G[to].push_back(m-1);
	}
	bool spfa(int& flow,int& cost)
	{
		memset(inq,0,sizeof inq);
		std::fill(d,d+n,INF);
		std::queue<int> que;
		que.push(s);
		d[s]=0;inq[s]=1;a[s]=INF;p[s]=0;
		while(!que.empty())
		{
			int u=que.front();que.pop();
			inq[u]=0;
			for(vit i=G[u].begin();i!=G[u].end();++i)
			{
				Edge& e=edges[*i];
				if(e.cap>e.flow && d[e.to]>d[u]+e.cost)
				{
					d[e.to]=d[u]+e.cost;
					p[e.to]=*i;
					a[e.to]=min(a[u],e.cap-e.flow);
					if(!inq[e.to]) que.push(e.to),inq[e.to]=1;
				}
			}
		}
		if(d[t]==INF) return 0;
		flow+=a[t];
		cost+=a[t]*d[t];
		for(int u=t;u!=s;u=edges[p[u]].from)
		{
			edges[p[u]].flow+=a[t];
			edges[p[u]^1].flow-=a[t];
		}
		return 1;
	}
	int mincost(int _s,int _t)
	{
		s=_s;t=_t;
		int flow=0,cost=0;
		while(spfa(flow,cost));
		return cost;
	}
	void init(int _n)
	{
		n=_n;
		for(int i=0;i<n;++i) G[i].clear();
		edges.clear();
	}
}M;
int n,m;
int s,t,ss,tt;
int du[MAXN];
int main()
{
	freopen("1.in","r",stdin);
	scanf("%d%d",&n,&m);
	M.init(2*n+4);
	s=0;t=2*n+1;
	ss=t+1;tt=ss+1;
	for(int i=1;i<=n;++i)
	{
		int tmp; scanf("%d",&tmp);
		M.addEdge(i,i+n,0,0);
		du[i]-=tmp; du[i+n]+=tmp;
	}
	M.addEdge(ss,s,m,0);
	for(int i=1;i<=n;++i) M.addEdge(s,i,INF,0);
	for(int i=1;i<=n;++i)
		for(int j=i+1;j<=n;++j)
		{
			int tmp; scanf("%d",&tmp);
			if(~tmp) M.addEdge(i+n,j,INF,tmp);
		}
	for(int i=1;i<=(n<<1);++i)
		if(du[i]>0) M.addEdge(ss,i,du[i],0);
		else if(du[i]<0) M.addEdge(i,tt,-du[i],0);
	printf("%d\n",M.mincost(ss,tt));
	return 0;
}
