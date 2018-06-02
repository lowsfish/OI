#include<cstdio>
#include<algorithm>
#include<cstring>
const int MAXN=50+5;
const int INF=1<<28;
int n,l;
int dp[MAXN][MAXN];
int len[MAXN];
int src(int i,int j)
{
	if(dp[i][j]>0) return dp[i][j];
	if(j-i<=1) return 0;
	int ans=INF;
	for(int k=i+1;k<j;++k)
		ans=std::min(ans,src(i,k)+src(k,j)+len[j]-len[i]);
	return dp[i][j]=ans;
}
int main()
{
	//freopen("1.in","r",stdin);
	while(scanf("%d%d",&l,&n)!=EOF && l)
	{
		for(int i=1;i<=n;++i) scanf("%d",len+i);
		len[n+1]=l;
		memset(dp,0,sizeof(dp));
		printf("The minimum cutting is %d.\n",src(0,n+1));
	}
	return 0;
}
