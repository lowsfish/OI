#include<iostream>
#include<cstdio>
#include<cstring>
#define MAXSZ 5010
using namespace std;
int par[MAXSZ],rank[MAXSZ];
void init(int n)
{
	for(int i=0;i<=n;++i)
	{
		par[i]=i;
		rank[i]=0;
	}
}

int find(int x)
{
	return par[x]==x?x:par[x]=find(par[x]);
}

void unite(int x,int y)
{
	x=find(x);y=find(y);
	if(x==y) return;
	if(rank[x]<rank[y])
	{
		par[x]=y;
	}
	else
	{
		par[y]=x;
		if(rank[x]==rank[y]) rank[x]++;
	}
}

bool same(int x,int y)
{
	return find(x)==find(y);
}

int main()
{
	//freopen("1.in","r",stdin);
	int n,m,p,i;
	cin>>n>>m>>p;
	init(n);
	for(i=0;i<m;++i)
	{
		int m1,m2;
		//cin>>m1>>m2;
		scanf("%d%d",&m1,&m2);
		--m1;--m2;
		unite(m1,m2);
	}
	for(i=0;i<p;++i)
	{
		int p1,p2;
		//cin>>p1>>p2;
		scanf("%d%d",&p1,&p2);
		--p1;--p2;
		if(same(p1,p2)) cout<<"Yes"<<endl;
		else cout<<"No"<<endl;
	}
	return 0;
}
