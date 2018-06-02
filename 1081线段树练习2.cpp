#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#define MAXSZ 400010
using namespace std;
int sumv[MAXSZ],minv[MAXSZ],maxv[MAXSZ],addv[MAXSZ];	
//sumv[o] represents that if only do node[o] and its subtrees' add operation,the sum of numbers in node[o]'s interval 
int y1,y2,v;	//make all the numbers in node[o]'s interval plus v 
//or query the sum of[y1,y2]
const int INF=1<<29;
int _min,_sum,_max,Ap;
int k,sumn;
int p;
int n,q;
void maintain(int o,int L,int R)	//maintain node[o],[L,R]
{
	int lc=o<<1,rc=(o<<1)+1;
	if(R>L)		//consider the subtrees
	{
		sumv[o]=minv[o]=maxv[o]=0;
		sumv[o]=sumv[lc]+sumv[rc];
		minv[o]=min(minv[lc],minv[rc]);
		maxv[o]=max(maxv[lc],maxv[rc]);
	}
	minv[o]+=addv[o];maxv[o]+=addv[o];sumv[o]+=addv[o]*(R-L+1);
	if(L==R) addv[o]=0;
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
		if(y1<=M) update(o*2,L,M);
		if(y2>M) update(o*2+1,M+1,R);
	}
	maintain(o,L,R);
}

void query(int o,int L,int R,int add)
{
	if(y1<=L && y2>=R)
	{
		_sum+=sumv[o]+add*(R-L+1);
		_min=min(_min,minv[o]+add);
		_max=max(_max,maxv[o]+add);
	}
	else
	{
		int M=L+(R-L)/2;
		if(y1<=M) query(o<<1,L,M,add+addv[o]);
		if(y2>M) query((o<<1)+1,M+1,R,add+addv[o]);
	}
}

void query2(int o,int L,int R) //query the value of A[p]
{
	int M=L+(R-L)/2;
	Ap+=addv[o];
	if(L==R) Ap+=maxv[o];
	else
	if(p<=M)
	{
		query2(o<<1,L,M);
	}
	else
	{
		query2((o<<1)+1,M+1,R);
	}
}

void init()
{
	k=0;
	while((1<<k)<n) ++k;
	sumn=1<<k;
	for(int i=0;i<=2*sumn;++i)
	{
		sumv[i]=addv[i]=0;
		maxv[i]=0;
		minv[i]=INF;
	}
}

void build(int o,int L,int R)
{
	if(L==R) return;
	int M=L+(R-L)/2;
	int lc=o<<1,rc=(o<<1)+1;
	build(lc,L,M);
	build(rc,M+1,R);
	sumv[o]=sumv[lc]+sumv[rc];
	maxv[o]=max(maxv[lc],maxv[rc]);
	minv[o]=min(minv[lc],minv[rc]);
}

int main()
{
	ios::sync_with_stdio(false);
	//freopen("1.in","r",stdin);
	cin>>n;
	init();
	for(int i=1;i<=n;++i)
	{
		int t;
		cin>>t;
		minv[sumn+i-1]=maxv[sumn+i-1]=sumv[sumn+i-1]=t;
	}
	build(1,1,sumn);
	cin>>q;
	for(int i=0;i<q;++i)
	{
		int t;
		cin>>t;
		if(t==1)
		{
			cin>>y1>>y2>>v;
			update(1,1,sumn);
		}
		else
		{
			Ap=0;
			cin>>p;
			query2(1,1,sumn);
			cout<<Ap<<endl;
		}
	}
	return 0;
}
