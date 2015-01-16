#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=10+2;
const int INF=1<<28;
int n;
int mat[MAXN][MAXN];
int dp[1<<MAXN][MAXN];
void floyd()
{
	for(int k=0;k<n;++k)
		for(int i=0;i<n;++i)
			for(int j=0;j<n;++j)
				mat[i][j]=min(mat[i][j],mat[i][k]+mat[k][j]);
}
int src(int S,int v)
{
	if(dp[S][v]>0) return dp[S][v];
	if(S==(1<<n)-1 && v==0) return dp[S][v]=0;
	int res=INF;
	for(int u=0;u<n;++u)
	{
		if(!((S>>u)&1)) res=min(res,src(S|(1<<u),u)+mat[v][u]);
	}
	return dp[S][v]=res;
}
int main()
{
	freopen("1.in","r",stdin);
	while(scanf("%d",&n)!=EOF && n)
	{
		++n;
		memset(dp,0,sizeof(dp));
		for(int i=0;i<n;++i)
			for(int j=0;j<n;++j)
				scanf("%d",&mat[i][j]);
		floyd();
		src(0,0);
		printf("%d\n",dp[0][0]);
	}
	return 0;
}
