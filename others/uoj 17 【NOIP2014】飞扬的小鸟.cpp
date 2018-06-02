#include<cstdio>
#include<algorithm>
const int MAXN=10000+5;
const int MAXM=1000+5;
const int INF=~0U>>2;
int dp[MAXN][MAXM];
int up[MAXN],down[MAXN],l[MAXN],h[MAXN];
int n,m,k;
void input()
{
	scanf("%d%d%d",&n,&m,&k);
	for(int i=0;i<n;++i) scanf("%d%d",up+i,down+i);
	while(k--)
	{
		int p;
		scanf("%d",&p);
		scanf("%d%d",l+p,h+p);
	}
}
void doDp()
{
	for(int i=1;i<=n;++i)
		for(int j=0;j<=m;++j)
			dp[i][j]=INF;
	for(int i=1;i<=n;++i)
	{
		for(int j=1;j<=m;++j)
		{
			int t=std::min(j+up[i-1],m);
			dp[i][t]=std::min(dp[i][t],std::min(dp[i-1][j],dp[i][j])+1);
		}
		for(int j=1;j<=m;++j)
			if(j-down[i-1]>0) dp[i][j-down[i-1]]=std::min(dp[i][j-down[i-1]],dp[i-1][j]);
		if(l[i]) for(int j=0;j<=l[i];++j) dp[i][j]=INF;
		if(h[i]) for(int j=h[i];j<=m;++j) dp[i][j]=INF;
	}
	int ans=INF;
	for(int i=1;i<=m;++i)
		ans=std::min(ans,dp[n][i]);
	if(ans<INF) printf("1\n%d\n",ans);
	else
	{
		ans=0;
		for(int i=1;i<=n;++i) if(l[i] || h[i])
		{
			for(int j=l[i]+1;j<h[i];++j) if(dp[i][j]!=INF)
			{
				++ans;
				break;
			}
		}
		printf("0\n%d\n",ans);
	}
}
int main()
{
	freopen("1.in","r",stdin);
	input();
	doDp();
	return 0;
}
