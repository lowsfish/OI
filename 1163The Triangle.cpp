#include<cstdio>
#include<algorithm>
const int MAXN=100+5;
int tr[MAXN][MAXN];
int dp[MAXN][MAXN];
int n;
int src(int x,int y)
{
	if(dp[x][y]>0) return dp[x][y];
	if(x==n-1) return dp[x][y]=tr[x][y];
	return dp[x][y]=std::max(src(x+1,y),src(x+1,y+1))+tr[x][y];
}
int main()
{
	scanf("%d",&n);
	for(int i=0;i<n;++i)
		for(int j=0;j<=i;++j)
		{
			scanf("%d",&tr[i][j]);
		}
	printf("%d\n",src(0,0));
	return 0;
}
