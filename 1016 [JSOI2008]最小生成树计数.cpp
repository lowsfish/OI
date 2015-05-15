#include<cstdio>
#include<algorithm>
const int MAXN=100+5;
const int MAXM=1000+5;
const int MOD=31011;
int n,m;
struct Edge{
	int u,v,c;
	bool operator<(const Edge& e)const
	{
		return c<e.c;
	}
}edges[MAXM];
int pa[MAXN];
void init()
{
	for(int i=1;i<=n;++i) pa[i]=i;
}
int find(int x)
{
	return pa[x]==x?x:find(pa[x]);
}
inline void unite(int x,int y)
{
	x=find(x);y=find(y);
	if(x==y) return;
	pa[x]=y;
}
int sum;
struct Node{
	int l,r,cnt;
}a[MAXM];
void dfs(int x,int cur,int c)
{
	if(cur>a[x].r)
	{
		if(c==a[x].cnt) ++sum;
		return;
	}
	int p=find(edges[cur].u),q=find(edges[cur].v);
	if(p!=q)
	{
		pa[p]=q;
		dfs(x,cur+1,c+1);
		pa[p]=p;pa[q]=q;
	}
	dfs(x,cur+1,c);
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=0;i<m;++i)
		scanf("%d%d%d",&edges[i].u,&edges[i].v,&edges[i].c);
	std::sort(edges,edges+m);
	init();
	int cnt=0,tot=0;
	a[0].l=0;a[0].cnt=0;
	for(int i=0;i<m;++i)
	{
		if(i!=0 && edges[i].c!=edges[i-1].c)
		{
			a[cnt].r=i-1;
			a[++cnt].l=i;
		}
		if(find(edges[i].u)!=find(edges[i].v))
		{
			unite(edges[i].u,edges[i].v);
			++a[cnt].cnt;
			++tot;
		}
	}
	a[cnt].r=m-1;
	if(tot<n-1)
	{
		puts("0");
		return 0;
	}
	init();
	int ans=1;
	for(int i=0;i<=cnt;++i)
	{
		sum=0;
		dfs(i,a[i].l,0);
		(ans*=sum)%=MOD;
		for(int j=a[i].l;j<=a[i].r;++j)
			unite(edges[j].u,edges[j].v);
	}
	printf("%d\n",ans);
	return 0;
}
