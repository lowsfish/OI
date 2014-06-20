#include<iostream>
#include<cstdio>
#include<cstring>
#define M 105
using namespace std;
int bit[M][M];
int W,H;
inline int lowbit(int x)
{
	return x&-x;
}

void init()
{
	memset(bit,0,sizeof(bit));
}
void update(int x,int y)
{
	for(int i=x;i<=W;i+=lowbit(i))
		for(int j=y;j<=H;j+=lowbit(j))
		{
			bit[i][j]+=1;
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
	freopen("1.in","r",stdin);
	int n,x,y,s,t,i,j,ans;
	while(cin>>n)
	{
		if(!n) return 0;
		init();
		ans=0;
		cin>>W>>H;
		for(i=0;i<n;++i)
		{
			cin>>x>>y;
			update(x,y);
		}
		cin>>s>>t;
		for(i=1;i<=W-s+1;++i)
			for(j=1;j<=H-t+1;++j)
			{
				int x1=i+s-1,y1=j+t-1;
				ans=max(ans,query(i,j,x1,y1));
			}
		cout<<ans<<endl;
	}

}
