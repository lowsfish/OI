#include<cstdio>
#include<algorithm>
const int MAXM=10+5;
const int MAXN=100+5;
const int INF=1<<28;
int mat[MAXM][MAXN];
int dp[MAXM][MAXN],nxt[MAXM][MAXN];
int n,m;
int main()
{
	//freopen("1.in","r",stdin);
	while(scanf("%d%d",&m,&n)!=EOF)
	{
		for(int i=0;i<m;++i)
			for(int j=0;j<n;++j)
				scanf("%d",&mat[i][j]),dp[i][j]=INF;
		for(int i=0;i<m;++i)
			dp[i][n-1]=mat[i][n-1];
		for(int j=n-2;j>=0;--j)
		{
			for(int i=0;i<m;++i)
			{
				int line[]={i-1,i,i+1};
				if(i==0) line[0]=m-1;
				if(i==m-1) line[2]=0;
				std::sort(line,line+3);
				for(int k=0;k<3;++k) if(dp[i][j]>dp[line[k]][j+1]+mat[i][j])
				{
					dp[i][j]=dp[line[k]][j+1]+mat[i][j];
					nxt[i][j]=line[k];
				}
			}
		}
		int ans=INF,one=0;
		for(int i=0;i<m;++i) if(dp[i][0]<ans) ans=dp[i][0],one=i;
		for(int i=0;i<n;++i)
		{
			printf("%d%c",one+1,i==n-1?'\n':' ');
			if(i!=n-1) one=nxt[one][i];
		}
		printf("%d\n",ans);
	}
	return 0;
}
