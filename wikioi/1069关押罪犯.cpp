#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=20000+10;
const int MAXM=100000+10;
struct node{
	int a,b,c;
	node() {}
	node(int a,int b,int c):a(a),b(b),c(c) {}
	bool operator<(const node &t) const
	{
		return c<t.c;
	}
}es[MAXM];
int pa[2*MAXN],rank[2*MAXN];
int n,m;

void init()
{
	for(int i=1;i<=2*n+10;++i) pa[i]=i;
}

int find(int x)
{
	return pa[x]==x?x:pa[x]=find(pa[x]);
}

void unite(int x,int y)
{
	x=find(x);y=find(y);
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

int main()
{
	scanf("%d%d",&n,&m);
	init();
	for(int i=0;i<m;++i)
	{
		int a,b,c;
		scanf("%d%d%d",&a,&b,&c);
		es[i]=node(a,b,c);
	}	
	sort(es,es+m);
	for(int i=m-1;i>=0;--i)
	{
		node nd=es[i];
		if(same(nd.a,nd.b) || same(nd.a+n,nd.b+n))
		{
			printf("%d\n",nd.c);
			return 0;
		}
		unite(nd.a,nd.b+n);
		unite(nd.a+n,nd.b);
	}
	printf("0\n");
	return 0;
}
