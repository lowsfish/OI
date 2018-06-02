#include<cstdio>
#include<algorithm>
#include<vector>
const int MAXN=10000+5;
using std::vector;
using std::min;
int n;
vector<int> G[MAXN];
typedef vector<int>::iterator vit;
int dp[MAXN][3];	//0:fa is,this isn't.1:fa and this aren't.2:this is
void src(int u,int fa)
{
	dp[u][0]=0;dp[u][2]=1;
	int sum=0;
	for(vit i=G[u].begin();i!=G[u].end();++i) if(*i!=fa)
	{
		src(*i,u);
		sum+=min(dp[*i][1],dp[*i][2]);
		dp[u][0]+=min(dp[*i][1],dp[*i][2]);
		dp[u][2]+=min(dp[*i][0],dp[*i][2]);
	}
	dp[u][1]=MAXN;
	for(vit i=G[u].begin();i!=G[u].end();++i) if(*i!=fa)
		dp[u][1]=min(dp[u][1],sum-min(dp[*i][1],dp[*i][2])+dp[*i][2]);
}
int main()
{
	freopen("1.in","r",stdin);
	int n;
	scanf("%d",&n);
	for(int i=0;i<n-1;++i)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		G[u].push_back(v);
		G[v].push_back(u);
	}
	src(1,0);
	printf("%d\n",min(dp[1][1],dp[1][2]));
	return 0;
}
