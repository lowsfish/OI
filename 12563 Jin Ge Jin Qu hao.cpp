#include<cstdio>
#include<algorithm>
#include<cstring>
const int MAXT=50*180+678+10;
const int MAXN=50+5;
int w[MAXN];
int dp[MAXT],d[MAXT];
int n,t,T;
void ZeroOne(int w,int v)
{
	for(int i=t-1;i>=v;--i) 
	{
		if(dp[i]<dp[i-w]+1)
		{
			dp[i]=dp[i-w]+1;
			d[i]=d[i-w]+v;
		}
		else if(dp[i]==dp[i-w]+1) d[i]=std::max(d[i],d[i-w]+v);
	}
}

int main()
{
	//freopen("1.in","r",stdin);
	scanf("%d",&T);
	for(int kase=1;kase<=T;++kase)
	{
		memset(dp,0,sizeof(dp));
		memset(d,0,sizeof(d));
		scanf("%d%d",&n,&t);
		for(int i=0;i<n;++i)
			scanf("%d",w+i);
		for(int i=0;i<n;++i)
			ZeroOne(w[i],w[i]);
		printf("Case %d: %d %d\n",kase,dp[t-1]+1,d[t-1]+678);
	}
	return 0;
}
