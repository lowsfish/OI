#include<cstdio>
#include<algorithm>
#include<cstring>
const int MAXN=1000+10;
const int INF=1<<28;
struct Node{
	int V,K,C,L;
	bool operator<(const Node& rhs)const
	{
		return V<rhs.V;
	}
}lamp[MAXN];
int n;
int dp[MAXN],sum[MAXN];
int src(int i)
{
	if(dp[i]>0) return dp[i];
	if(i==0) return dp[i]=lamp[i].L*lamp[i].C+lamp[i].K;
	int ans=sum[i]*lamp[i].C+lamp[i].K;
	for(int j=0;j<i;++j)
	{
		ans=std::min(ans,src(j)+(sum[i]-sum[j])*lamp[i].C+lamp[i].K);
	}
	return dp[i]=ans;
}
int main()
{
	//freopen("1.in","r",stdin);
	while(scanf("%d",&n)!=EOF && n)
	{
		memset(dp,0,sizeof(dp));
		for(int i=0;i<n;++i)
			scanf("%d%d%d%d",&lamp[i].V,&lamp[i].K,&lamp[i].C,&lamp[i].L);
		std::sort(lamp,lamp+n);
		sum[0]=lamp[0].L;
		for(int i=1;i<n;++i) sum[i]=sum[i-1]+lamp[i].L;
		printf("%d\n",src(n-1));
	}
	return 0;
}
