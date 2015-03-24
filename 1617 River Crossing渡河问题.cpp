#include<cstdio>
#include<cstring>
#include<algorithm>
const int MAXN=2500+5;
int sum[MAXN];
int dp[MAXN];
int n,m;
int src(int s)
{
	if(s<=0) return 0;
	if(s==1) return sum[1];
	int& ans=dp[s];
	if(ans>=0) return ans;
	ans=sum[s];
	for(int i=1;i<s;++i)
		ans=std::min(ans,src(i)+sum[s-i]+m);
	return ans;
}

int main()
{
	freopen("1.in","r",stdin);
	memset(dp,-1,sizeof(dp));
	scanf("%d%d",&n,&m);
	sum[0]=m;
	for(int i=1;i<=n;++i)
	{
		int t;
		scanf("%d",&t);
		sum[i]=sum[i-1]+t;
	}
	printf("%d\n",src(n));
	return 0;
}
