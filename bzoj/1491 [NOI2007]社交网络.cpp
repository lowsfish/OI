#include<cstdio>
#include<algorithm>
const int MAXN=100+2;
const int INF=~0U>>2;
const double eps=1e-10;
typedef long long LL;
LL dist[MAXN][MAXN],num[MAXN][MAXN];
int n,m;
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i)
		for(int j=1;j<=n;++j)
			dist[i][j]=i==j?0:INF;
	for(int i=0;i<m;++i)
	{
		int u,v,c;
		scanf("%d%d%d",&u,&v,&c);
		dist[u][v]=dist[v][u]=c;
		num[u][v]=num[v][u]=1;
	}
	for(int k=1;k<=n;++k)
		for(int i=1;i<=n;++i)
			for(int j=1;j<=n;++j)
			{
				if(dist[i][k]+dist[k][j]<dist[i][j])
				{
					dist[i][j]=dist[i][k]+dist[k][j];
					num[i][j]=num[i][k]*num[k][j];
				}
				else if(dist[i][k]+dist[k][j]==dist[i][j])
					num[i][j]+=num[i][k]*num[k][j];
			}
	for(int k=1;k<=n;++k)
	{
		double ans=0.0;
		for(int i=1;i<=n;++i)
			for(int j=1;j<=n;++j)
			{
				if(i==k || j==k || i==j) continue;
				if(dist[i][k]+dist[k][j]==dist[i][j])
				ans+=(double)num[i][k]*num[k][j]/num[i][j];
			}
		printf("%.3f\n",ans+eps);
	}
	return 0;
}
