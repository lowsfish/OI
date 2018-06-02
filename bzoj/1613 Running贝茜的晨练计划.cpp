#include<cstdio>
#include<algorithm>
const int MAXN=10000+5;
const int MAXM=500+5;
int dp[MAXN][MAXM];
int d[MAXN];
int n,m;
int main()
{
	freopen("1.in","r",stdin);
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i) scanf("%d",d+i);
	for(int i=1;i<=n;++i)
		for(int j=0;j<=std::min(m,i);++j)
		{
			if(j<m && i<n) dp[i+1][j+1]=std::max(dp[i+1][j+1],dp[i][j]+d[i]);
			if(i+j<=n+1) dp[i+j][0]=std::max(dp[i+j][0],dp[i][j]);
			if(j==0) dp[i+1][0]=std::max(dp[i+1][0],dp[i][j]);
		}
	printf("%d\n",dp[n+1][0]);
	return 0;
}
