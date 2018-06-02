#include<cstdio>
#include<algorithm>
#include<cstring>
const int MAXN=1000+5;
const int INF=1<<28;
char s[MAXN];
bool p[MAXN][MAXN];
int dp[MAXN];
int T,n;
int src(int i)
{
	if(dp[i]>0) return dp[i];
	if(p[0][i+1]) return dp[i]=1;
	int ans=INF;
	for(int j=0;j<i;++j) if(p[j+1][i-j])
		ans=std::min(ans,src(j)+1);
	return dp[i]=ans;
}
int main()
{
	//freopen("1.in","r",stdin);
	scanf("%d",&T);
	while(T--)
	{
		scanf("%s",s);
		n=strlen(s);
		for(int i=0;i<n;++i) p[i][1]=1,p[i][0]=1;
		for(int j=2;j<=n;++j)
			for(int i=0;i<n;++i)
			{
				if(i+j-1>=n) break;
				p[i][j]=(p[i+1][j-2]&&s[i]==s[i+j-1]);
			}
		memset(dp,0,sizeof(dp));
		printf("%d\n",src(n-1));
	}
	return 0;
}
