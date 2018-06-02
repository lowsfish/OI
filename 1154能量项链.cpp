#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
const int MAXN=100+5;
int a[MAXN];
int dp[MAXN<<1][MAXN<<1];
int n;
int main()
{
	freopen("1.in","r",stdin);
	scanf("%d",&n);
	for(int i=0;i<n;++i)
	{
		scanf("%d",a+i);
		a[i+n]=a[i];
	}
	int ans=0;
	for(int j=1;j<n+n;++j)
		for(int i=j-1;i>=0 && j-i<n;--i)
			for(int k=i;k<j;++k)
			{
				dp[i][j]=max(dp[i][j],dp[i][k]+dp[k+1][j]+a[i]*a[k+1]*a[j+1]);
				ans=max(ans,dp[i][j]);
			}
	printf("%d\n",ans);
	return 0;
}
