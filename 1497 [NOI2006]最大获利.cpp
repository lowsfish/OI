#include<cstdio>
#include<algorithm>
#include<vector>
#include<queue>
using std::vector;
using std::min;
using std::fill;
const int MAXN=5000+5;
const int MAXM=50000+5;
const int INF=~0U>>1;
struct Edge{
	int from,to,cap,flow;
	Edge(int from,int to,int cap,int flow):
		from(from),to(to),cap(cap),flow(flow) {}
};
typedef vector<int>::iterator vit;
struct Dinic{
	int n,m,s,t;
	vector<Edge> edges;
	vector<int> G[MAXN+MAXM];
	int d[MAXN+MAXM];
	vit cur[MAXN+MAXM];
	bool vis[MAXN+MAXM];
	inline void addEdge(int from,int to,int cap,int rev=0)
	{
		edges.push_back(Edge(from,to,cap,0));
		edges.push_back(Edge(to,from,rev,0));
		m=edges.size();
		G[from].push_back(m-2);
		G[to].push_back(m-1);
	}
	bool bfs()
	{
		std::queue<int> que;
		fill(vis,vis+n,0);
		que.push(s);vis[s]=1;d[s]=0;
		while(!que.empty())
		{
			int u=que.front();que.pop();
			for(vit i=G[u].begin();i!=G[u].end();++i)
			{
				Edge& e=edges[*i];
				if(e.cap>e.flow && !vis[e.to])
				{
					vis[e.to]=1;
					d[e.to]=d[u]+1;
					que.push(e.to);
				}
			}
		}
		return vis[t];
	}
	int dfs(int u,int a)
	{
		if(u==t || a==0) return a;
		int flow=0,f;
		for(vit& i=cur[u];i!=G[u].end();++i)
		{
			Edge& e=edges[*i];
			if(d[e.to]==d[u]+1 && (f=dfs(e.to,min(a,e.cap-e.flow)))>0)
			{
				flow+=f;
				a-=f;
				e.flow+=f;
				edges[(*i)^1].flow-=f;
				if(a==0) break;
			}
		}
		return flow;
	}
	int maxflow(int _s,int _t)
	{
		s=_s;t=_t;
		int flow=0;
		while(bfs())
		{
			for(int i=0;i<n;++i) cur[i]=G[i].begin();
			flow+=dfs(s,INF);
		}
		return flow;
	}
	void init(int _n)
	{
		n=_n;
		for(int i=0;i<n;++i) G[i].clear();
		edges.clear();
	}
}S;
int n,m;
int w[MAXN];
int main()
{
	scanf("%d%d",&n,&m);
	int s=0,t=n+m+1;
	S.init(n+m+2);
	for(int i=1;i<=n;++i) scanf("%d",w+i),S.addEdge(i+m,t,w[i]);
	int sum=0;
	for(int i=1;i<=m;++i)
	{
		int a,b,c;
		scanf("%d%d%d",&a,&b,&c);
		sum+=c;
		S.addEdge(s,i,c);
		S.addEdge(i,a+m,INF);
		S.addEdge(i,b+m,INF);
	}
	printf("%d\n",sum-S.maxflow(s,t));
	return 0;
}
