#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;
struct Edge{
	int from,to,cap,flow,cost;
	Edge(int from,int to,int cost):from(from),to(to),cost(cost) {}
};
const int MAXN=500+10;
const int INF=1<<28;
int mat[MAXN][MAXN];
struct POINT{
	int x,y,b;
}bd[105],fs[105];
inline int dist(POINT a,POINT b)
{
	return abs(a.x-b.x)+abs(a.y-b.y)+1;
}
struct MCMF{
	int n,m,s,t;
	vector<Edge> edges;
	vector<int> G[MAXN];
	bool inq[MAXN],used[MAXN];
	int d[MAXN],p[MAXN],cnt[MAXN],sum[MAXN];
	void init(int n)
	{
		this->n=n;
		edges.clear();
		for(int i=0;i<n;++i) G[i].clear();
	}
	void addedge(int from,int to,int cost)
	{
		edges.push_back(Edge(from,to,cost));
		m=edges.size();
		G[from].push_back(m-1);
	}
	void build(int n,int m)
	{
		memset(sum,0,sizeof(sum));
		for(int j=1;j<=m;++j)
		{
			int sum=0;
			for(int i=1;i<=n;++i)
			{
				int cost=dist(bd[i],fs[j]);
				addedge(i,j+n,cost);
				if(mat[i][j]>0) addedge(j+n,i,-cost);
				sum+=mat[i][j];
			}
			if(sum>0) addedge(t,j+n,0);
			if(sum<fs[j].b) addedge(j+n,t,0);
		}
	}
	int spfa()
	{
		queue<int> que;
		for(int i=0;i<n;++i) inq[i]=0,d[i]=INF,cnt[i]=0;
		inq[t]=1;d[t]=0;p[t]=0;cnt[t]=1;
		que.push(t);
		while(!que.empty())
		{
			int u=que.front();que.pop();
			inq[u]=0;
			for(int i=0;i<G[u].size();++i)
			{
				Edge &e=edges[G[u][i]];
				if(d[e.to]>d[u]+e.cost)
				{
					d[e.to]=d[u]+e.cost;
					p[e.to]=G[u][i];
					if(!inq[e.to]) 
					{
						inq[e.to]=1;
						que.push(e.to);
						cnt[e.to]++;
						if(cnt[e.to]>n) return e.to;
					}
				}
			}
		}
		return -1;
	}
	void solve(int n,int m,int s,int t)
	{
		memset(used,0,sizeof(used));
		this->s=s;this->t=t;
		build(n,m);
		int st=spfa();
		if(st==-1) printf("OPTIMAL\n");
		else
		{
			printf("SUBOPTIMAL\n");
			while(1)
			{
				if(!used[st]) used[st]=1,st=edges[p[st]].from;
				else break;
			}
			int u=st;
			do{
				int from=edges[p[u]].from;
				if(from<=n && from>0) mat[from][u-n]++;
				else if(u<=n && u>0)mat[u][from-n]--;
				u=from;
			}while(u!=st);
			for(int i=1;i<=n;++i)
				for(int j=1;j<=m;++j)
					printf("%d%c",mat[i][j],j==m?'\n':' ');
		}
	}
}mcmf;

int n,m;
int main()
{
	while(scanf("%d%d",&n,&m)!=EOF)
	{
		mcmf.init(n+m+2);
		for(int i=1;i<=n;++i) scanf("%d%d%d",&bd[i].x,&bd[i].y,&bd[i].b);
		for(int i=1;i<=m;++i) scanf("%d%d%d",&fs[i].x,&fs[i].y,&fs[i].b);
		for(int i=1;i<=n;++i)
			for(int j=1;j<=m;++j)
				scanf("%d",&mat[i][j]);
		mcmf.solve(n,m,0,n+m+1);
	}
	return 0;
}
