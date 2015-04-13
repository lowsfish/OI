#include<cstdio>
#include<vector>
#include<queue>
#include<algorithm>
#include<cstring>
const int MAXN=2000*2000;
const int INF=~0U>>1;
struct Edge{
	int to,cost;
	Edge(int to,int cost):to(to),cost(cost) {}
};
std::vector<Edge> G[MAXN];
typedef std::vector<Edge>::iterator it;
int d[MAXN];
bool inq[MAXN];
int n,m,V;
int spfa(int s,int t)
{
	for(int i=0;i<V;++i) d[i]=i==s?0:INF;
	std::queue<int> que;
	que.push(s);
	inq[s]=1;
	while(!que.empty())
	{
		int x=que.front();que.pop();
		inq[x]=0;
		for(it e=G[x].begin();e!=G[x].end();++e) if(d[e->to]>d[x]+e->cost)
		{
			d[e->to]=d[x]+e->cost;
			if(!inq[e->to]) que.push(e->to),inq[e->to]=1;
		}
	}
	return d[t];
}
inline void addEdge(int u,int v,int c)
{
	G[u].push_back(Edge(v,c));
	G[v].push_back(Edge(u,c));
}
int main()
{
	//freopen("1.in","r",stdin);
	scanf("%d%d",&n,&m);
	int line=(m-1)<<1;
	V=(n-1)*(m-1)*2+2;
	for(int i=0;i<n;++i)
		for(int j=1;j<m;++j)
		{
			int t;scanf("%d",&t);
			if(i==0) addEdge(V-1,j<<1,t);
			else if(i==n-1) addEdge(0,(i-1)*line+j*2-1,t);
			else addEdge((i-1)*line+j*2-1,i*line+j*2,t);
		}
	for(int i=1;i<n;++i)
		for(int j=1;j<=m;++j)
		{
			int t;scanf("%d",&t);
			if(j==1) addEdge(0,(i-1)*line+1,t);
			else if(j==m) addEdge(V-1,(i-1)*line+(j-1)*2,t);
			else addEdge((i-1)*line+(j-1)*2,(i-1)*line+j*2-1,t);
		}
	for(int i=0;i<n-1;++i)
		for(int j=1;j<m;++j)
		{
			int t;scanf("%d",&t);
			addEdge(i*line+j*2-1,i*line+j*2,t);
		}
	printf("%d\n",spfa(0,V-1));
	return 0;
}

