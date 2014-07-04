#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXSZ=105;
int fa[MAXSZ*MAXSZ];
int rank[MAXSZ*MAXSZ];
struct edge{
	int from,to,cost;
	edge() {}
	edge(int from,int to,int cost):from(from),to(to),cost(cost) {}
};

bool cmp(const edge &a,const edge &b)
{
	return a.cost<b.cost;
}
edge es[MAXSZ*MAXSZ];
int V,E=0;

void init()
{
	for(int i=0;i<V;++i)
	{
		fa[i]=i;
		rank[i]=0;
	}
}

int getfa(int x)
{
	return fa[x]==x?x:fa[x]=getfa(fa[x]);
}

void unite(int x,int y)
{
	x=getfa(x);
	y=getfa(y);
	if(x==y) return;
	if(rank[x]<rank[y])
	{
		fa[x]=y;
	}
	else
	{
		fa[y]=x;
		if(rank[x]==rank[y]) rank[x]++;
	}
}

bool same(int x,int y)
{
	return getfa(x)==getfa(y);
}
int kruskal()
{
	init();
	sort(es,es+E,cmp);
	int ans=0;
	for(int i=0;i<E;++i)
	{
		edge e=es[i];
		if(!same(e.from,e.to))
		{
			ans+=e.cost;
			unite(e.from,e.to);
		}
	}
	return ans;
}

int main()
{
	//freopen("1.in","r",stdin);
	cin>>V;
	for(int i=0;i<V;++i)
		for(int j=0;j<V;++j)
		{
			int t;
			cin>>t;
			if(t!=0)
			{
				es[E++]=edge(i,j,t);
			}
		}
	cout<<kruskal()<<endl;
	return 0;
}
