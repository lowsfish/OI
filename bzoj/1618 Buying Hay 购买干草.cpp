#include<cstdio>
#include<algorithm>
const int MAXM=50000+5;
const int MAXN=100+5;
const int MAXC=5000;
const int INF=~0U>>2;
int dp[MAXM+MAXC];
int n,m;
inline void Complete(int w,int v)
{
	for(int i=w;i<=m+MAXC;++i)
		dp[i]=std::min(dp[i],dp[i-w]+v);
}
int p[MAXN],c[MAXN];
int main()
{
	freopen("1.in","r",stdin);
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m+MAXC;++i) dp[i]=INF;
	for(int i=0;i<n;++i) scanf("%d%d",p+i,c+i);
	for(int i=0;i<n;++i)
		Complete(p[i],c[i]);
	int ans=INF;
	for(int i=m;i<=m+MAXC;++i) ans=std::min(ans,dp[i]);
	printf("%d\n",ans);
	return 0;
}
