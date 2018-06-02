#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#include<queue>
using namespace std;
struct Edge{
	int from,to,cap,flow,cost;
	Edge(int from,int to,int cap,int flow,int cost):from(from),to(to),cap(cap),flow(flow),cost(cost) {}
};
const int MAXN=1000+10;
const int INF=1<<28;
struct MCMF{
	int n,m,s,t;
	vector<Edge> edges;
	vector<int> G[MAXN];
	int d[MAXN],a[MAXN],p[MAXN];
	bool inq[MAXN];
	void addedge(int from,int to,int cap,int cost)
	{
		edges.push_back(Edge(from,to,cap,0,cost));
		edges.push_back(Edge(to,from,0,0,-cost));
		m=edges.size();
		G[from].push_back(m-2);
		G[to].push_back(m-1);
	}
	bool spfa(int &flow,int& cost)
	{
		memset(inq,0,sizeof(inq));
		for(int i=0;i<n;++i) d[i]=INF;
		queue<int> que;
		d[s]=0;a[s]=INF;inq[s]=1;p[s]=0;
		que.push(s);
		while(!que.empty())
		{
			int u=que.front();que.pop();
			inq[u]=0;
			for(int i=0;i<G[u].size();++i)
			{
				Edge &e=edges[G[u][i]];
				if(e.cap>e.flow && d[e.to]>d[u]+e.cost)
				{
					a[e.to]=min(a[u],e.cap-e.flow);
					d[e.to]=d[u]+e.cost;
					p[e.to]=G[u][i];
					if(!inq[e.to]) que.push(e.to),inq[e.to]=1;
				}
			}
		}
		if(d[t]==INF) return 0;
		flow+=a[t];
		cost+=d[t];
		int u=t;
		while(u!=s)
		{
			edges[p[u]].flow+=a[t];
			edges[p[u]^1].flow-=a[t];
			u=edges[p[u]].from;
		}
		return 1;
	}
	int mincost(int s,int t)
	{
		this->s=s;this->t=t;
		int flow=0,cost=0;
		while(spfa(flow,cost));
		return cost;
	}
}mcmf;
int n,m;
int main()
{
	freopen("1.in","r",stdin);
	scanf("%d%d",&n,&m);
	mcmf.n=n+2;
	while(m--)
	{
		int u,v,cost;
		scanf("%d%d%d",&u,&v,&cost);
		mcmf.addedge(u,v,1,cost);
		mcmf.addedge(v,u,1,cost);
	}
	mcmf.addedge(0,1,2,0);
	mcmf.addedge(n,n+1,2,0);
	printf("%d\n",mcmf.mincost(0,n+1));
	return 0;
}
