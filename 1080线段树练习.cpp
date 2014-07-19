#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long LL;
const int MAXSZ=100001;
LL bit[MAXSZ];
int n;
inline int lowbit(int x)
{
	return x&-x;
}

void update(int x,int a)
{
	for(int i=x;i<=n;i+=lowbit(i))
	{
		bit[i]+=a;
	}
}

LL getsum(int x)
{
	LL ans=0;
	for(int i=x;i>0;i-=lowbit(i))
	{
		ans+=bit[i];
	}
	return ans;
}

LL query(int l,int r)
{
	return getsum(r)-getsum(l-1);
}

void init()
{
	for(int i=0;i<=n;++i)
	{
		bit[i]=0;
	}
}

int main()
{
//	freopen("1.in","r",stdin);
	cin>>n;
	init();
	for(int i=1;i<=n;++i)
	{
		int t;
		cin>>t;
		update(i,t);
	}
	int m;
	cin>>m;
	for(int i=0;i<m;++i)
	{
		int q,a,b;
		cin>>q;
		if(q==1)
		{
			cin>>a>>b;
			update(a,b);
		}
		else
		{
			cin>>a>>b;
			cout<<query(a,b)<<endl;
		}
	}
	return 0;
} 
