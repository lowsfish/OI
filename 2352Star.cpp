#include<iostream>
#include<cstdio>
#include<algorithm>
#define M 15010
#define XMAX 32001
using namespace std;
int c[XMAX],n,ans[M];
int a[M];

int lowbit(int x)
{
	return x&(-x);
}

void update(int x)
{
	while(x<=XMAX)		//注意不是n
	{
		++c[x];
		x+=lowbit(x);
	}

}

int getsum(int x)
{
	int ans=0;
	while(x>0)
	{
		ans+=c[x];
		x-=lowbit(x);
	}
	return ans;
}
int main()
{
	freopen("1.in","r",stdin);
	int k;
	cin>>n;
	for(int i=1;i<=n;++i)
	{
		cin>>a[i]>>k;
		++a[i];		//注意坐标有可能是0
	}
	for(int i=1;i<=n;++i)
	{
		ans[getsum(a[i])]++;
		update(a[i]);
	}
	for(int i=0;i<n;++i) cout<<ans[i]<<endl;
	return 0;
}
