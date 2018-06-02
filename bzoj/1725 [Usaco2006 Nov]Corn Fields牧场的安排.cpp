#include<cstdio>
#include<cstring>
const int MAXN=13;
const int MOD=100000000;
int dp[MAXN][1<<MAXN];
int mat[13];
int n,m;
void input()
{
	scanf("%d%d",&n,&m);
	for(int i=0;i<n;++i)
		for(int j=0;j<m;++j)
		{
			int t;
			scanf("%d",&t);
			mat[i]<<=1;mat[i]|=t;
		}
}
inline bool judge(int i,int S)
{
	return (S&(S>>1)) || ((S|mat[i])!=mat[i]);
}
int src(int cur,int S)
{
	int& ans=dp[cur][S];
	if(ans>=0) return ans;
	if(judge(cur,S)) return ans=0;
	if(cur==0) return 1;
	ans=0;
	for(int i=0;i<(1<<m);++i)
		if(!(i&S))
		ans=(ans+src(cur-1,i))%MOD;
	return ans;
}
int main()
{
	freopen("1.in","r",stdin);
	input();
	memset(dp,-1,sizeof dp);
	int ans=0;
	for(int i=0;i<(1<<m);++i) ans=(ans+src(n-1,i))%MOD;
	printf("%d\n",ans);
	return 0;
}
