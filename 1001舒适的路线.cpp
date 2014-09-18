#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int INF=(1<<29)-1;
const int MAXN=500+10;
const int MAXM=5000+10;
int rank[MAXN],pa[MAXN];
int n,m,s,t;
double ans=(double)INF;
int t1,t2;
struct edge{
	int u,v,cost;
	edge() {}
	edge(int u,int v,int cost):u(u),v(v),cost(cost) {}
	bool operator<(const edge &a) const
	{
		return cost<a.cost;
	}
}es[MAXM];
void init()
{
	for(int i=0;i<=n;++i)
	{
		rank[i]=0;
		pa[i]=i;
	}
}

int find(int x)
{
	return pa[x]==x?x:pa[x]=find(pa[x]);
}

void unite(int x,int y)
{
	x=find(x);
	y=find(y);
	if(x==y) return;
	if(rank[x]<rank[y])
	{
		pa[x]=y;
	}
	else
	{
		pa[y]=x;
		if(rank[x]==rank[y]) ++rank[x];
	}
}

bool same(int x,int y)
{
	return find(x)==find(y);
}

inline int gcd(int a,int b)
{
	return b==0?a:gcd(b,a%b);
}

void print(int a,int b)
{
	if(b%a==0)
	{
		printf("%d\n",b/a);
		return;
	}
	int t=gcd(a,b);
	a/=t;b/=t;
	printf("%d/%d",b,a);
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=0;i<m;++i)
	{
		int u,v,cost;
		scanf("%d%d%d",&u,&v,&cost);
		es[i]=edge(u,v,cost);
	}
	scanf("%d%d",&s,&t);
	sort(es,es+m);
	for(int i=0;i<m;++i)
	{
		init();
		int maxc=es[i].cost;
		for(int j=i;j>=0;--j)
		{
			unite(es[j].u,es[j].v);
			if(same(s,t))
			{
				int minc=es[j].cost;
				double t=(double)maxc/(double)minc;
				if(t<ans)
				{
					t1=minc;
					t2=maxc;
					ans=t;
				}
				break;
			}
		}
	}
	if((int)ans==INF) printf("IMPOSSIBLE\n");
	else print(t1,t2);
	return 0;
}
