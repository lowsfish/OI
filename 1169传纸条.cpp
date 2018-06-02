#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
const int MAXN=50+5;
int dp[MAXN<<1][MAXN][MAXN],mat[MAXN][MAXN];
int m,n;

int main()
{
	freopen("1.in","r",stdin);
	scanf("%d%d",&m,&n);
	for(int i=0;i<m;++i)
		for(int j=0;j<n;++j)
		{
			scanf("%d",&mat[i][j]);
		}
	dp[0][0][0]=mat[0][0];
	int step=(n-1)+(m-1);
	for(int i=1;i<=step;++i)
		for(int j=0;j<=i && j<n;++j)
			for(int k=0;k<=i && k<n;++k)
			{
				if(i-k>=m || i-j>=m) continue;
				int plus=mat[i-k][k]+mat[i-j][j];
				if(j==k) plus=mat[i-k][k];
				if(j>0 && i-1>=k && dp[i-1][j-1][k]+plus>dp[i][j][k]) dp[i][j][k]=dp[i-1][j-1][k]+plus;
				if(k>0 && i-1>=j && dp[i-1][j][k-1]+plus>dp[i][j][k])dp[i][j][k]=dp[i-1][j][k-1]+plus;
				if(i-1>=j && i-1>=k && dp[i-1][j][k]+plus>dp[i][j][k]) dp[i][j][k]=dp[i-1][j][k]+plus;
				if(k>0 && j>0 && dp[i-1][j-1][k-1]+plus>dp[i][j][k]) dp[i][j][k]=dp[i-1][j-1][k-1]+plus;
			}
	printf("%d\n",dp[step][n-1][n-1]);
	return 0;
}
