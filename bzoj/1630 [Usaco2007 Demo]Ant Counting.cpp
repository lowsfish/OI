#include<cstdio>
const int MOD=1000000;
int dp[1000005];
int a[1005],sum[1000005];
int t,m,s,b;
int main()
{
	//freopen("1.in","r",stdin);
	scanf("%d%d%d%d",&t,&m,&s,&b);
	for(int i=0;i<m;++i)
	{
		int x;
		scanf("%d",&x);
		a[x]++;
	}
	for(int i=0;i<=a[1];++i) dp[i]=1;
	for(int i=2;i<=t;++i)
	{
		sum[0]=1;
		for(int j=1;j<=b;++j) sum[j]=(sum[j-1]+dp[j])%MOD;
		for(int j=b;j>=1;--j)
		{
			if(j<=a[i]) dp[j]=sum[j]%MOD;
			else dp[j]=(sum[j]-sum[j-a[i]-1])%MOD;
		}
	}
	int ans=0;
	for(int i=s;i<=b;++i) ans=(ans+dp[i])%MOD;
	printf("%d\n",ans);
}
