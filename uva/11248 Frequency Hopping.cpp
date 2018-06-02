#include<cstdio>
#include<cstring>
#include<vector>
#include<queue>
#include<algorithm>
const int MAXN=100+5;
const int INF=1<<28;
struct Edge{
	int from,to,cap,flow;
	Edge(int from,int to,int cap,int flow):from(from),to(to),cap(cap),flow(flow) {}
	bool operator<(const Edge& rhs)const
	{
		return from<rhs.from || (from==rhs.from && to<rhs.to);
	}
};
struct Dinic{
	int n,m,s,t;
	std::vector<Edge> edges;
	std::vector<int> G[MAXN];
	bool vis[MAXN];
	int cur[MAXN],d[MAXN];
	void addedge(int from,int to,int cap)
	{
		edges.push_back(Edge(from,to,cap,0));;
		edges.push_back(Edge(to,from,0,0));
		m=edges.size();
		G[from].push_back(m-2);
		G[to].push_back(m-1);
	}
	bool bfs()
	{
		std::queue<int> que;
		memset(vis,0,sizeof(vis));
		d[s]=0;vis[s]=1;
		que.push(s);
		while(!que.empty())
		{
			int u=que.front();que.pop();
			for(int i=0;i<G[u].size();++i)
			{
				Edge& e=edges[G[u][i]];
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
		for(int &i=cur[u];i<G[u].size();++i)
		{
			Edge& e=edges[G[u][i]];
			if(d[u]+1==d[e.to] && e.cap>e.flow && (f=dfs(e.to,std::min(a,e.cap-e.flow)))>0)
			{
				e.flow+=f;
				edges[G[u][i]^1].flow-=f;
				a-=f;
				flow+=f;
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
	std::vector<int> mincut()
	{
		std::vector<int> cut;
		for(int i=0;i<m;++i)
		{
			Edge& e=edges[i];
			if(vis[e.from] && !vis[e.to] && e.cap>0)
				cut.push_back(i);
		}
		return cut;
	}
	void clearflow()
	{
		for(int i=0;i<m;++i)
			edges[i].flow=0;
	}
	void init(int n)
	{
		this->n=n;
		edges.clear();
		for(int i=1;i<=n;++i) G[i].clear();
	}
	void reduce()
	{
		for(int i=0;i<m;++i) edges[i].cap-=edges[i].flow;
		clearflow();
	}
}dc;
int n,e,c;
int main()
{
	//freopen("1.in","r",stdin);
	int kase=0;
	while(scanf("%d%d%d",&n,&e,&c)!=EOF && n)
	{
		dc.init(n);
		while(e--)
		{
			int u,v,cap;
			scanf("%d%d%d",&u,&v,&cap);
			dc.addedge(u,v,cap);
		}
		int flow=dc.maxflow(1,n);
		printf("Case %d: ",++kase);
		if(flow>=c) printf("possible\n");
		else
		{
			std::vector<int> cut=dc.mincut();
			dc.reduce();
			std::vector<Edge> ans;
			for(int i=0;i<cut.size();++i)
			{
				dc.clearflow();
				Edge& e=dc.edges[cut[i]];
				e.cap=c;
				int f=dc.maxflow(1,n);
				if(flow+f>=c) ans.push_back(e);
				e.cap=0;
			}
			if(ans.empty()) printf("not possible\n");
			else
			{
				std::sort(ans.begin(),ans.end());
				printf("possible option:");
				for(int i=0;i<ans.size();++i)
				{
					Edge e=ans[i];
					printf("(%d,%d)%c",e.from,e.to,i==ans.size()-1?'\n':',');
				}
			}
		}
	}
	return 0;
}
