#include<cstdio>
#include<cstring>
const int MAXN=1000+5;
bool mat[MAXN][MAXN];
int link[MAXN];
bool used[MAXN];
int n,m;
bool find(int x)
{
	for(int i=0;i<n;++i) if(mat[x][i] && !used[i])
	{
		used[i]=1;
		if(link[i]==0 || find(link[i])) {link[i]=x;return 1;}
	}
	return 0;
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;++i)
	{
		int a,b;
		scanf("%d%d",&a,&b);
		mat[i][a]=mat[i][b]=1;
	}
	int ans=0;
	for(int i=1;i<=m;++i)
	{
		memset(used,0,sizeof(used));
		if(find(i)) ans++;
		else break;
	}
	printf("%d\n",ans);
	return 0;
}
