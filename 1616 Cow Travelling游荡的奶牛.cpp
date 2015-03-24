#include<cstdio>
#include<cstring>
#include<iostream>
const int MAXN=100+5;
const int MAXT=15+5;
char mat[MAXN][MAXN];
int dp[MAXT][MAXN][MAXN];
int n,m,T,r1,c1,r2,c2;
int dx[]={0,-1,0,1},dy[]={1,0,-1,0};
int src(int t,int x,int y)
{
	if(x<0 || y<0 || x>=n || y>=m) return 0;
	if(mat[x][y]=='*') return 0;
	if(t==0) return x==r1 && y==c1;
	int& ans=dp[t][x][y];
	if(ans>=0) return ans;
	ans=0;
	for(int i=0;i<4;++i)
	{
		int nx=x+dx[i],ny=y+dy[i];
		ans+=src(t-1,nx,ny);
	}
	return ans;
}
int main()
{
	freopen("1.in","r",stdin);
	scanf("%d%d%d",&n,&m,&T);
	getchar();
	for(int i=0;i<n;++i)
		std::cin.getline(mat[i],MAXN);
	scanf("%d%d%d%d",&r1,&c1,&r2,&c2);
	--r1;--c1;--r2;--c2;
	memset(dp,-1,sizeof dp);
	printf("%d\n",src(T,r2,c2));
	return 0;
}
