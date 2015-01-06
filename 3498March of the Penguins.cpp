#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#include<queue>
#include<algorithm>
#include<cmath>
using namespace std;
struct Edge{
	int from,to,cap,flow;
	Edge(int from,int to,int cap,int flow):from(from),to(to),cap(cap),flow(flow) {}
};
const int MAXN=500+5;
const int INF=1<<28;
struct Dinic{
	int n,m,s,t;
	vector<Edge> edges;
	vector<int> G[MAXN];
	bool vis[MAXN];
	int d[MAXN],cur[MAXN];
	void init(int n)
	{
		this->n=n;
		edges.clear();
		for(int i=0;i<=n;++i) G[i].clear();
	}
	void addedge(int from,int to,int cap)
	{
		edges.push_back(Edge(from,to,cap,0));
		edges.push_back(Edge(to,from,0,0));
		m=edges.size();
		G[from].push_back(m-2);
		G[to].push_back(m-1);
	}
	bool bfs()
	{
		memset(vis,0,sizeof(vis));
		queue<int> que;
		que.push(s);
		d[s]=0;
		vis[s]=1;
		while(!que.empty())
		{
			int x=que.front();que.pop();
			for(int i=0;i<G[x].size();++i)
			{
				Edge &e=edges[G[x][i]];
				if(!vis[e.to] && e.cap>e.flow)
				{
					que.push(e.to);
					d[e.to]=d[x]+1;
					vis[e.to]=1;
				}
			}
		}
		return vis[t];
	}
	int dfs(int x,int a)
	{
		if(x==t || a==0) return a;
		int flow=0,f;
		for(int &i=cur[x];i<G[x].size();++i)
		{
			Edge &e=edges[G[x][i]];
			if(d[e.to]==d[x]+1 && (f=dfs(e.to,min(a,e.cap-e.flow)))>0)
			{
				e.flow+=f;
				edges[G[x][i]^1].flow-=f;
				flow+=f;
				a-=f;
				if(a==0) break;
			}
		}
		return flow;
	}
	int maxflow(int s,int t)
	{
		this->s=s;this->t=t;
		int flow=0;
		while(bfs())
		{
			memset(cur,0,sizeof(cur));
			flow+=dfs(s,INF);
		}
		return flow;
	}
	void clearflow()
	{
		for(int i=0;i<edges.size();++i) edges[i].flow=0;
	}
}dinic;
typedef pair<int,int> P;
#define fi first
#define se second
P po[MAXN];
inline double dist(P a,P b)
{
	int dx=a.fi-b.fi,dy=a.se-b.se;
	return sqrt((double)(dx*dx+dy*dy));
}
int T,n,X[MAXN],Y[MAXN];
double D;
int main()
{
//	freopen("1.in","r",stdin);
	scanf("%d",&T);
	while(T--)
	{
		int sum=0;
		scanf("%d%lf",&n,&D);
		dinic.init(n+n+2);
		for(int i=1;i<=n;++i) scanf("%d%d%d%d",&po[i].fi,&po[i].se,X+i,Y+i);
		for(int i=1;i<=n;++i) sum+=X[i];
		for(int i=1;i<=n;++i) dinic.addedge(i,i+n,Y[i]);
		for(int i=1;i<=n;++i)
			for(int j=i+1;j<=n;++j)
				if(dist(po[i],po[j])<=D) 
					dinic.addedge(i+n,j,INF),dinic.addedge(j+n,i,INF);	
		for(int i=1;i<=n;++i) if(X[i]>0) dinic.addedge(0,i,X[i]);
		bool flag=0;
		for(int i=1;i<=n;++i)
		{
			dinic.clearflow();
			int ans=dinic.maxflow(0,i);
			if(ans==sum)
			{
				if(!flag) flag=1;
				else putchar(' ');
				printf("%d",i-1);
			}
		}
		if(!flag) printf("-1");
		putchar(10);
	}
	return 0;
}
