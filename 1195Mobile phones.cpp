#include<iostream>
#include<cstdio>
#define M 1030
using namespace std;
int bit[M][M],n;

int lowbit(int x)
{
	return x&(-x);
}

void update(int x,int y,int a)
{
	for(int i=x;i<=n;i+=lowbit(i))
		for(int j=y;j<=n;j+=lowbit(j))
		{
			bit[i][j]+=a;
		}
}

int getsum(int x,int y)
{
	int ans=0;
	for(int i=x;i>0;i-=lowbit(i))
		for(int j=y;j>0;j-=lowbit(j))
		{
			ans+=bit[i][j];
		}
	return ans;
}

int query(int x1,int y1,int x2,int y2)
{
	int ans=getsum(x2,y2)-getsum(x2,y1-1)-getsum(x1-1,y2)+getsum(x1-1,y1-1);
	return ans;	
}
int main()
{
	//freopen("1.in","r",stdin);
	int q,x,y,a,x1,y1,i;
	cin>>q>>n;
	++n;
	while(cin>>q)
	{
		if(q==3) return 0;
		if(q==1)
		{
			cin>>x>>y>>a;
			++x;++y;
			update(x,y,a);
		}
		if(q==2)
		{
			cin>>x>>y>>x1>>y1;
			++x;++y;++y1;++x1;
			cout<<query(x,y,x1,y1)<<endl;
		}
	}
	return 0;
}
