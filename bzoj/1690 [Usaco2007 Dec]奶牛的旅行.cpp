#include<cstdio>
#include<algorithm>
#include<vector>
#include<cstring>
const int MAXN=1000+5;
const double eps=1e-10;
using std::vector;
struct Edge{
	int v,t;
	double c;
	Edge(int v,int t):v(v),t(t) {}
};
typedef vector<Edge>::iterator vit;
vector<Edge> G[MAXN];
int w[MAXN];
double d[MAXN];
bool vis[MAXN];
bool spfa(int u)
{
	vis[u]=1;
	for(vit e=G[u].begin();e!=G[u].end();++e) if(d[e->v]>d[u]+e->c)
	{
		d[e->v]=d[u]+e->c;
		if(vis[e->v] || spfa(e->v)) return 1;
	}
	vis[u]=0;
	return 0;
}
int n,m;
void rebuild(double x)
{
	for(int i=1;i<=n;++i)
		for(vit e=G[i].begin();e!=G[i].end();++e)
			e->c=-w[e->v]+ e->t * x;
}
bool judge()
{
	std::fill(vis+1,vis+n+1,0);
	std::fill(d+1,d+n+1,0);
	for(int i=1;i<=n;++i) if(spfa(i))
		return 1;
	return 0;
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i) scanf("%d",w+i);
	for(int i=1;i<=m;++i)
	{
		int u,v,t;
		scanf("%d%d%d",&u,&v,&t);
		G[u].push_back(Edge(v,t));
	}
	double L=0,R=1001;
	while(R-L>1e-3)
	{
		double M=(L+R)/2;
		rebuild(M);
		if(judge()) L=M;
		else R=M;
	}
	printf("%.2f\n",L+eps);
	return 0;
}
