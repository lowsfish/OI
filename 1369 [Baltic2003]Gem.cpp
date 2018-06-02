#include<cstdio>
#include<algorithm>
#include<vector>
const int MAXN=10000+5;
const int INF=~0U>>1;
int dp[MAXN][11];
std::vector<int> G[MAXN];
typedef std::vector<int>::iterator vit;
int n;
int src(int u,int k,int fa)
{
	int& ans=dp[u][k];
	if(ans>0) return ans;
	ans=k;
	for(vit e=G[u].begin();e!=G[u].end();++e) if(*e!=fa)
	{
		int t=INF;
		for(int j=1;j<=10;++j) if(j!=k)
			t=std::min(t,src(*e,j,u));
		ans+=t;
	}
	return ans;
}
int main()
{
//	freopen("1.in","r",stdin);
	scanf("%d",&n);
	for(int i=0;i<n-1;++i)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		G[u].push_back(v);
		G[v].push_back(u);
	}
	int ans=INF;
	for(int i=1;i<=10;++i) ans=std::min(ans,src(1,i,0));
	printf("%d\n",ans);
	return 0;
}
