#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;
struct Edge{
	int from,to,cap,flow;
	bool flag;	//是否需要判断路径长度
	Edge(int from,int to,int cap,int flow):from(from),to(to),cap(cap),flow(flow) {}
};
const int MAXN=300+5;
const int INF=1<<28;
int mat[MAXN][MAXN];
int K,C,M;
struct Dinic{
	int n,m,s,t;
	vector<Edge> edges;
	vector<int> G[MAXN];
	bool vis[MAXN];
	int d[MAXN],cur[MAXN];
	inline void addedge(int from,int to,int cap)
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
		d[s]=0;vis[s]=1;
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
		for(int& i=cur[x];i<G[x].size();++i)
		{
			Edge &e=edges[G[x][i]];
			if(d[e.to]==d[x]+1 && (f=dfs(e.to,min(a,e.cap-e.flow)))>0)
			{
				a-=f;
				flow+=f;
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
	void init(int n)
	{
		this->n=n;
		edges.clear();
		for(int i=0;i<n;++i) G[i].clear();
	}
	void build(int k,int n)
	{
		init(n+2);
		for(int i=K+1;i<=n;++i) addedge(0,i,1);
		for(int i=1;i<=K;++i) addedge(i,n+1,M);
		for(int i=K+1;i<=n;++i)
			for(int j=1;j<=K;++j)
				if(mat[i][j]<=k) addedge(i,j,1);
	}
}dinic;
int n;
int main()
{
	freopen("1.in","r",stdin);
	scanf("%d%d%d",&K,&C,&M);
	n=K+C;
	for(int i=1;i<=n;++i)
		for(int j=1;j<=n;++j)
		{
			scanf("%d",&mat[i][j]);
			if(mat[i][j]==0) mat[i][j]=INF;
		}
	int L=1,R=10000;
	for(int k=1;k<=n;++k)
		for(int i=1;i<=n;++i)
			for(int j=1;j<=n;++j)
			{
				mat[i][j]=min(mat[i][j],mat[i][k]+mat[k][j]);
				if(mat[i][j]==INF) continue;
				R=max(R,mat[i][j]);
			}
	/*for(int i=1;i<=n;++i)
	{
		for(int j=1;j<=n;++j) printf("%d ",mat[i][j]);
		putchar(10);
	}*/
	int ans=INF;
	while(L<R) //[L,R)
	{
		int mid=(L+R)>>1;
		dinic.build(mid,n);
		if(dinic.maxflow(0,n+1)>=C) R=mid;
		else L=mid+1;
	}
	printf("%d\n",R);
	return 0;
}
