#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
const int MAXN=(1<<19)+10;
typedef long long LL;
LL sumv[MAXN],_sum;
LL addv[MAXN];
LL y1,y2,v;
LL totn,n,m;

void maLLain(LL o,LL L,LL R)
{
	LL lc=o<<1;LL rc=lc+1;
	if(R>L)
	{
		sumv[o]=sumv[lc]+sumv[rc];
	}
	sumv[o]+=addv[o]*(R-L+1);
	if(L==R) addv[o]=0;
}

void update(LL o,LL L,LL R)
{
	if(y1<=L && y2>=R)
	{
		addv[o]+=v;
	}
	else
	{
		LL M=L+(R-L)/2,lc=o<<1;
		LL rc=lc+1;
		if(y1<=M) update(lc,L,M);
		if(y2>M) update(rc,M+1,R);
	}
	maLLain(o,L,R);
}

void query(LL o,LL L,LL R,LL add)
{
	if(y1<=L && y2>=R) _sum+=sumv[o]+add*(R-L+1);
	else
	{
		LL M=L+(R-L)/2,lc=o<<1;
		LL rc=lc+1;
		if(y1<=M) query(lc,L,M,add+addv[o]);
		if(y2>M) query(rc,M+1,R,add+addv[o]);
	}
}

void init()
{
	totn=1;
	while(totn<n) totn<<=1;
	memset(sumv,0,sizeof(sumv));
	memset(addv,0,sizeof(addv));	
}

void build(LL o,LL L,LL R)
{
	if(L==R) return;
	LL M=L+(R-L)/2,lc=o<<1;
	LL rc=lc+1;
	build(lc,L,M);
	build(rc,M+1,R);
	sumv[o]+=sumv[lc]+sumv[rc];
}

int main()
{
	//freopen("1.in","r",stdin);
	scanf("%lld",&n);
	init();
	for(LL i=0;i<n;++i)
	{
		scanf("%lld",sumv+totn+i);
	}
	build(1,1,totn);
	scanf("%lld",&m);
	while(m--)
	{
		LL q;
		scanf("%lld",&q);
		if(q==1)
		{
			scanf("%lld%lld%lld",&y1,&y2,&v);
			update(1,1,totn);
		}
		else
		{
			scanf("%lld%lld",&y1,&y2);
			_sum=0;
			query(1,1,totn,0);
			printf("%lld\n",_sum);
		}
	}
	return 0;
}
