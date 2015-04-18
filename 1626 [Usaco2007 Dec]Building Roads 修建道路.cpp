#include<cstdio>
#include<cmath>
#include<algorithm>
const int MAXN=1005+5;
int pa[MAXN];
int n,m;
struct Edge{
	int u,v;
	double c;
	Edge() {}
	Edge(int u,int v,double c):u(u),v(v),c(c) {}
	bool operator<(const Edge& e) const
	{
		return c<e.c;
	}
}e[MAXN*MAXN];
int ne;
bool have[MAXN][MAXN];
typedef std::pair<int,int> P;
#define x first
#define y second
inline double dist(P a,P b)
{
	double dx=a.x-b.x,dy=a.y-b.y;
	return sqrt(dx*dx+dy*dy);
}
P pt[MAXN];
int find(int x)
{
	return pa[x]==x?x:pa[x]=find(pa[x]);
}
void unite(int x,int y)
{
	x=find(x);y=find(y);
	if(x==y) return;
	pa[x]=y;
}
double kruskal()
{
	std::sort(e,e+ne);
	for(int i=0;i<n;++i) pa[i]=i;
	for(int i=0;i<n;++i)
		for(int j=0;j<n;++j) if(have[i][j])
			unite(i,j);
	double ans=0;
	for(int i=0;i<ne;++i) if(find(e[i].u)!=find(e[i].v))
	{
		unite(e[i].u,e[i].v);
		ans+=e[i].c;
	}
	return ans;
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=0;i<n;++i) scanf("%d%d",&pt[i].x,&pt[i].y);
	while(m--)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		--u;--v;
		have[u][v]=have[v][u]=1;
	}
	ne=0;
	for(int i=0;i<n;++i)
		for(int j=i+1;j<n;++j) if(!have[i][j])
			e[ne++]=Edge(i,j,dist(pt[i],pt[j]));
	printf("%.2f\n",kruskal());
	return 0;
}
