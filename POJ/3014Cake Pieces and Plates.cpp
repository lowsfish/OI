#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
const int MOD=1000000007;
const int MAXNM=4500+5;
int n,m;
int dp[MAXNM][MAXNM];
void solve()
{
	dp[0][0]=1;
	for(int i=1;i<=n;++i)
		for(int j=0;j<=m;++j)
		{
			if(j-i>=0) dp[i][j]=(dp[i-1][j]+dp[i][j-i])%MOD;
			else dp[i][j]=dp[i-1][j];
		}
	printf("%d\n",dp[n][m]);
}
int main()
{
	scanf("%d%d",&n,&m);
	solve();
	return 0;
}
