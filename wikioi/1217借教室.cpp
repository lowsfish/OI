#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
const int MAXSZ=2*(1<<20)+100;
const int INF=1<<29;
int minv[MAXSZ],addv[MAXSZ];
int k,sumn,n,m;
int _min;
int y1,y2,v;
void maintain(int o,int L,int R)
{
	if(R>L)
	{
		minv[o]=0;
		minv[o]=min(minv[o<<1],minv[(o<<1)+1]);
	}
	minv[o]+=addv[o];
	if(R==L) addv[o]=0;
}

void update(int o,int L,int R)
{
	if(y1<=L && y2>=R)
	{
		addv[o]+=v;
	}
	else
	{
		int M=L+(R-L)/2;
		if(y1<=M) update(o<<1,L,M);
		if(y2>M) update((o<<1)+1,M+1,R);
	}
	maintain(o,L,R);
}

void query(int o,int L,int R,int add)
{
	if(y1<=L && y2>=R)
	{
		_min=min(_min,minv[o]+add);
	}
	else
	{
		int M=L+(R-L)/2;
		if(y1<=M) query(o<<1,L,M,add+addv[o]);
		if(y2>M) query((o<<1)+1,M+1,R,add+addv[o]);
	}
}

void init()
{
	int k=0;
	while((1<<k)<n) ++k;
	sumn=1<<k;
	memset(minv,0,sizeof(minv));
	memset(addv,0,sizeof(addv));
}

void build(int o,int L,int R)
{
	if(L==R) return;
	int M=L+(R-L)/2,lc=o<<1,rc=(o<<1)+1;
	build(lc,L,M);
	build(rc,M+1,R);
	minv[o]=min(minv[o<<1],minv[(o<<1)+1]);
}
void solve()
{
	scanf("%d%d",&n,&m);
	init();
	for(int i=1;i<=n;++i)
	{
		int t;
		scanf("%d",&t);
		minv[i+sumn-1]=t;
	}
	build(1,1,sumn);
	for(int i=1;i<=m;++i)
	{
		cin>>v>>y1>>y2;
		v=-v;
		update(1,1,sumn);
		_min=INF;
		query(1,1,sumn,0);
		if(_min<0)
		{
			printf("-1\n%d\n",i);
			return;
		}
	}
	printf("0\n");
}

int main()
{
	freopen("1.in","r",stdin);
	solve();
	return 0;
}
