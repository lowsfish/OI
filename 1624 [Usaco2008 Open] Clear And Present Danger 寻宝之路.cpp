#include<cstdio>
#include<algorithm>
const int MAXN=100+5;
const int MAXM=10000+5;
int mat[MAXN][MAXN];
int n,m;
int a[MAXM];
void floyd()
{
	for(int k=1;k<=n;++k)
		for(int i=1;i<=n;++i)
			for(int j=1;j<=n;++j)
				mat[i][j]=std::min(mat[i][j],mat[i][k]+mat[k][j]);
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=0;i<m;++i) scanf("%d",a+i);
	for(int i=1;i<=n;++i)
		for(int j=1;j<=n;++j)
			scanf("%d",&mat[i][j]);
	floyd();
	int ans=0;
	for(int i=0;i<m-1;++i)
		ans+=mat[a[i]][a[i+1]];
	printf("%d\n",ans);
	return 0;
}
