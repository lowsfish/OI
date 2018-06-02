#include<cstdio>
#include<algorithm>
const int MAXN=300+10;
int mat[MAXN][MAXN];
int w[MAXN];
int pa[MAXN*MAXN+MAXN];
struct Edge{
	int u,v,c;
	Edge(){}
	Edge(int u,int v,int c):u(u),v(v),c(c) {}
	bool operator<(const Edge& rhs)const
	{
		return c<rhs.c;
	}
}edges[MAXN*MAXN+MAXN];
int find(int x)
{
	return pa[x]==x?x:pa[x]=find(pa[x]);
}
int main()
{
	//freopen("1.in","r",stdin);
	int n,w,cnt=0,ans=0;
	scanf("%d",&n);
	for(int i=1;i<=n;++i)
	{
		scanf("%d",&w);
		edges[cnt++]=Edge(0,i,w);
	}
	for(int i=1;i<=n;++i)
		for(int j=1;j<=n;++j)
		{
			scanf("%d",&w);
			edges[cnt++]=Edge(i,j,w);
		}
	std::sort(edges,edges+cnt);
	for(int i=1;i<=n;++i) pa[i]=i;
	for(int i=0;i<cnt;++i)
	{
		Edge e=edges[i];
		if(find(e.u)!=find(e.v)) pa[find(e.v)]=find(e.u),ans+=e.c;
	}
	printf("%d\n",ans);
	return 0;
}
