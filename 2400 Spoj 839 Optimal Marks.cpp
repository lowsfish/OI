#include<cstdio>
#include<cstring>
#include<vector>
#include<queue>
#include<algorithm>
typedef long long LL;
const int MAXN=500+5;
const int MAXM=2000+5;
const int INF=~0U>>2;
using std::vector;
using std::fill;
using std::min;
using std::max;
typedef vector<int>::iterator vit;
struct Edge{
	int from,to,cap,flow;
	Edge(int u,int v,int c,int f):from(u),to(v),cap(c),flow(f) {}
};
struct Dinic{
	int n,m,s,t;
	vector<Edge> edges;
	vector<int> G[MAXN];
	int cur[MAXN],d[MAXN];
	bool vis[MAXN];
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
		fill(vis,vis+n,0);
		std::queue<int> que;
		que.push(s);
		d[s]=0;vis[s]=1;
		while(!que.empty())
		{
			int u=que.front();que.pop();
			for(vit i=G[u].begin();i!=G[u].end();++i)
			{
				Edge& e=edges[*i];
				if(e.cap>e.flow && !vis[e.to])
				{
					d[e.to]=d[u]+1;
					vis[e.to]=1;
					que.push(e.to);
				}
			}
		}
		return vis[t];
	}
	int dfs(int u,int a)
	{
		if(a==0 || u==t) return a;
		int flow=0,f;
		for(int& i=cur[u];i<G[u].size();++i)
		{
			Edge& e=edges[G[u][i]];
			if(d[e.to]==d[u]+1 && (f=dfs(e.to,min(a,e.cap-e.flow)))>0)
			{
				flow+=f;
				e.flow+=f;
				a-=f;
				edges[G[u][i]^1].flow-=f;
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
			fill(cur,cur+n,0);
			flow+=dfs(s,INF);
		}
		return flow;
	}
	void init(int _n)
	{
		n=_n;
		edges.clear();
		for(int i=0;i<n;++i) G[i].clear();
	}
}S;
int n,m;
int w[MAXN];
int u[MAXM],v[MAXM];
int main()
{
	scanf("%d%d",&n,&m);
	S.init(n+2);
	int mx=0;
	for(int i=1;i<=n;++i) scanf("%d",w+i),mx=max(mx,w[i]);
	for(int i=0;i<m;++i)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		::u[i]=u;
		::v[i]=v;
	}
	int log=0;
	for(;(1<<log)<=mx;++log);--log;
	int s=0,t=n+1;
	LL ans1=0,ans2=0;
	for(;log>=0;--log)
	{
		S.init(n+2);
		for(int i=1;i<=n;++i) if(w[i]>=0)
		{
			if(w[i]&(1<<log)) S.addEdge(s,i,INF),S.addEdge(i,t,1);
			else S.addEdge(i,t,INF);
		}
		else S.addEdge(i,t,1);
		for(int i=0;i<m;++i) S.addEdge(u[i],v[i],MAXM,MAXM);
		int flow=S.maxflow(0,n+1);
		ans1+=1LL*(flow/MAXM)*(1<<log);
		ans2+=1LL*(flow%MAXM)*(1<<log);
	}
	printf("%lld\n%lld\n",ans1,ans2);
	return 0;
}
