#include<cstdio>
#include<cstring>
const int MAXN=100+5;
double dp[MAXN][MAXN];
int main()
{
	int T;
	scanf("%d",&T);
	for(int kase=1;kase<=T;++kase)
	{
		int a,b,n;
		scanf("%d/%d%d",&a,&b,&n);
		double p=(double)a/b;
		memset(dp,0,sizeof dp);
		dp[0][0]=1;dp[0][1]=0;
		for(int i=1;i<=n;++i)
			for(int j=0;j*b<=a*i;++j)
			{
				dp[i][j]=dp[i-1][j]*(1-p);
				if(j) dp[i][j]+=dp[i-1][j-1]*p;
			}
		double Q=0;
		for(int j=0;j*b<=a*n;++j) Q+=dp[n][j];
		printf("Case #%d: %d\n",kase,(int)(1/Q));
	}
	return 0;
}
