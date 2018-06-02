#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
const int MAXN=2*(1<<18)+100;
int sumv[MAXN],setv[MAXN];
int y1,y2,v;
int n,k,sumn,m;
int _sum;
void init()
{
	k=0;
	while((1<<k)<n) ++k;
	sumn=1<<k;
	memset(sumv,0,sizeof(sumv));
	memset(setv,-1,sizeof(setv));
	for(int i=1;i<=n;++i)
	{
		sumv[i+sumn-1]=1;
	}
}

void maintain(int o,int L,int R)
{
	if(setv[o]>=0)
	{
		sumv[o]=setv[o]*(R-L+1);
	}
	else if(R>L)
	{
		int lc=o<<1;
		int rc=lc+1;
		sumv[o]=sumv[lc]+sumv[rc];
	}
}

void pushdown(int o)
{
	if(setv[o]>=0)
	{
		int lc=o<<1;
		int rc=lc+1;
		setv[lc]=setv[rc]=setv[o];
		setv[o]=-1;
	}
}
void update(int o,int L,int R)
{
	if(y1<=L && y2>=R)
	{
		setv[o]=v;
	}
	else
	{
		pushdown(o);
		int M=L+(R-L)/2,lc=o<<1;
		int rc=lc+1;
		if(y1<=M) update(lc,L,M);else maintain(lc,L,M);
		if(y2>M) update(rc,M+1,R);else maintain(rc,M+1,R);	
	}
	maintain(o,L,R);
}

void query(int o,int L,int R)
{
	if(setv[o]>=0)
	{
		_sum+=setv[o]*(min(R,y2)-max(L,y1)+1);
	}
	else if(y1<=L && y2>=R)
	{
		_sum+=sumv[o];
	}
	else
	{
		int M=L+(R-L)/2,lc=o<<1;
		int rc=lc+1;
		if(y1<=M) query(lc,L,M);
		if(y2>M) query(rc,M+1,R);
	}
}

void build(int o,int L,int R)
{
	if(L==R) return;
	int M=L+(R-L)/2,lc=o<<1;
	int rc=lc+1;
	build(lc,L,M);
	build(rc,M+1,R);
	sumv[o]=sumv[lc]+sumv[rc];
}

int main()
{
	//freopen("1.in","r",stdin);
	scanf("%d%d",&n,&m);
	init();
	build(1,1,sumn);
	v=0;
	for(int i=0;i<m;++i)
	{
		scanf("%d%d",&y1,&y2);
		update(1,1,sumn);
		y1=1;y2=n;_sum=0;
		query(1,1,sumn);
		printf("%d\n",_sum);
	}
	return 0;
}
