/*
By:lowsfish
Time:2014.6.29
Result:Accepted
*/
#include<iostream>
#include<cstdio>
#include<cstring>
#define MAXK 100010
#define MAXN 50010
using namespace std;
int N,K;
int T[MAXK],X[MAXK],Y[MAXK];
int par[3*MAXN];
int rank[3*MAXN];
void init(int n)
{
	for(int i=0;i<n;++i) 
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
	x=find(x);
	y=find(y);
	if(x==y) return;
	if(rank[x]<rank[y])
	{
		par[x]=y;
	}
	else
	{
		par[y]=par[x];
		if(rank[x]==rank[y]) ++rank[x];
	}
}

bool same(int x,int y)
{
	return find(x)==find(y);
}
void solve()
{
	init(N*3);
	int ans=0;
	for(int i=0;i<K;++i)
	{
		int t=T[i];
		int x=X[i]-1,y=Y[i]-1;
		if(x<0 || x>=N || y<0 || y>=N)
		{
			++ans;
			continue;
		}
		if(t==1)
		{
			if(same(x,y+N) || same(x,y+2*N))
				++ans;
			else
			{
				unite(x,y);
				unite(x+N,y+N);
				unite(x+2*N,y+2*N);
			}
		}
		else
		{
			if(same(x,y) || same(x,y+2*N))
				++ans;
			else
			{
				unite(x,y+N);
				unite(x+N,y+2*N);
				unite(x+2*N,y);
			}
		}
	}
	cout<<ans<<endl;
}

int main()
{
	//freopen("1.in","r",stdin);
	cin>>N>>K;
	for(int i=0;i<K;++i)
	{
		//cin>>T[i]>>X[i]>>Y[i];
		scanf("%d%d%d",&T[i],&X[i],&Y[i]);
	}
	solve();
	return 0;
}
