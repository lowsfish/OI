#include<cstdio>
#include<algorithm>
#include<vector>
const int MAXN=2000+5;
std::vector<int> G[MAXN];
int dp[MAXN],n;
int L[MAXN],W[MAXN];
int src(int x)
{
	if(dp[x]>0) return dp[x];
	int ans=1;
	for(int i=0;i<G[x].size();++i)
		ans=std::max(ans,src(G[x][i])+1);
	return dp[x]=ans;
}
int main()
{
	freopen("1.in","r",stdin);
	scanf("%d",&n);
	for(int i=0;i<n;++i) scanf("%d%d",L+i,W+i);
	for(int i=0;i<n;++i)
		for(int j=0;j<n;++j)
		{
			if(i==j) continue;
			if((L[i]<L[j] && W[i]<W[j]) || (L[i]<W[j] && W[i]<L[j]))
				G[i].push_back(j);
		}
	for(int i=0;i<n;++i) if(!dp[i]) src(i);
	int ans=1;
	for(int i=0;i<n;++i) ans=std::max(ans,dp[i]);
	printf("%d\n",ans);
	return 0;
}
