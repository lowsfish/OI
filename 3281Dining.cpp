#include<iostream>
#include<cstdio>
#include<queue>
#include<cstring>
#include<vector>
using namespace std;
struct Edge{
	int from,to,cap,flow;
	Edge(int from,int to,int cap,int flow):from(from),to(to),cap(cap),flow(flow) {}
};
const int MAXN=400+10;
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
	bool bfs()
	{
		memset(vis,0,sizeof(vis));
		queue<int> que;
		que.push(s);
		vis[s]=1;
		d[s]=0;
		while(!que.empty())
		{
			int x=que.front();que.pop();
			for(int i=0;i<G[x].size();++i)
			{
				Edge &e=edges[G[x][i]];
				if(!vis[e.to] && e.cap>e.flow)
				{
					que.push(e.to);
					vis[e.to]=1;
					d[e.to]=d[x]+1;
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
			Edge& e=edges[G[x][i]];
			if(d[x]+1==d[e.to] && (f=dfs(e.to,min(a,e.cap-e.flow)))>0)
			{
				e.flow+=f;
				flow+=f;
				edges[G[x][i]^1].flow-=f;
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
}dinic;
int N,F,D;
int main()
{
	freopen("1.in","r",stdin);
	scanf("%d%d%d",&N,&F,&D);
	dinic.n=N+N+F+D+2;
	for(int i=1;i<=N;++i)
	{
		int n1,n2;
		scanf("%d%d",&n1,&n2);
		dinic.addedge(F+i,F+N+i,1);
		while(n1--)
		{
			int food;
			scanf("%d",&food);
			dinic.addedge(food,F+i,1);
		}
		while(n2--)
		{
			int drink;
			scanf("%d",&drink);
			dinic.addedge(F+N+i,F+N+N+drink,1);
		}
	}
	for(int i=1;i<=F;++i) dinic.addedge(0,i,1);
	for(int i=1;i<=D;++i) dinic.addedge(F+N+N+i,dinic.n-1,1);
	printf("%d\n",dinic.maxflow(0,dinic.n-1));
	return 0;
}
