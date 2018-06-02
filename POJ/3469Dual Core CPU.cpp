#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
#include<vector>
#include<queue>
using namespace std;
struct Edge{
	int from,to,cap,flow;
	Edge(int from,int to,int cap,int flow):from(from),to(to),cap(cap),flow(flow) {}
};
const int MAXN=20000+10;
const int INF=1<<28;
struct Dinic{
	int n,m,s,t;
	vector<Edge> edges;
	vector<int> G[MAXN];
	bool vis[MAXN];
	int d[MAXN],cur[MAXN];
	void addedge(int from,int to,int cap)
	{
		edges.push_back(Edge(from,to,cap,0));
		edges.push_back(Edge(to,from,0,0));
		m=edges.size();
		G[from].push_back(m-2);
		G[to].push_back(m-1);
	}
	void init(int n)
	{
		this->n=n;
		for(int i=0;i<n;++i) G[i].clear();
		edges.clear();
	}
	bool bfs()
	{
		memset(vis,0,sizeof(vis));
		queue<int> que;
		vis[s]=1;d[s]=0;
		que.push(s);
		while(!que.empty())
		{
			int x=que.front();que.pop();
			for(int i=0;i<G[x].size();++i)
			{
				Edge &e=edges[G[x][i]];
				if(!vis[e.to] && e.cap>e.flow)
				{
					d[e.to]=d[x]+1;
					vis[e.to]=1;
					que.push(e.to);
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
			if(d[x]+1==d[e.to] && (f=dfs(e.to,min(a,e.cap-e.flow)))>0)
			{
				flow+=f;
				a-=f;
				e.flow+=f;
				edges[G[x][i]^1].flow-=f;
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
}dinic;
int n,m;
int main()
{
	//freopen("1.in","r",stdin);
	scanf("%d%d",&n,&m);
	dinic.init(n+2);
	for(int i=1;i<=n;++i)
	{
		int a,b;
		scanf("%d%d",&a,&b);
		dinic.addedge(0,i,a);
		dinic.addedge(i,n+1,b);
	}
	while(m--)
	{
		int u,v,c;
		scanf("%d%d%d",&u,&v,&c);
		dinic.addedge(u,v,c);
		dinic.addedge(v,u,c);
	}
	printf("%d\n",dinic.maxflow(0,n+1));
	return 0;
}
