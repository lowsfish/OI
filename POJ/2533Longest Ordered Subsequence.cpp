#include<cstdio>
#include<algorithm>
const int MAXN=1000+5;
const int INF=1<<20;
int a[MAXN],dp[MAXN],n;
void solve()
{
	std::fill(dp,dp+n,INF);
	for(int i=0;i<n;++i) *std::lower_bound(dp,dp+n,a[i])=a[i];
	printf("%d\n",(int)(std::lower_bound(dp,dp+n,INF)-dp));
}
int main()
{
	scanf("%d",&n);
	for(int i=0;i<n;++i) scanf("%d",a+i);
	solve();
	return 0;
}
