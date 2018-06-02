#include<cstdio>
#include<algorithm>
#include<cstring>
const int MAXN=700+5;
int mat[MAXN][MAXN];
bool forbid[MAXN][MAXN];
int dp[MAXN][MAXN];
int n,m;
int dx[]={-1,0,1,0},dy[]={0,1,0,-1};
int src(int x,int y)
{
	int& ans=dp[x][y];
	if(ans!=-1) return ans;
	ans=1;
	for(int i=0;i<4;++i)
	{
		int nx=x+dx[i],ny=y+dy[i];
		if(nx>=1 && nx<=n && ny>=1 && ny<=n && !forbid[nx][ny] && mat[nx][ny]<mat[x][y])
			ans=std::max(ans,src(nx,ny)+1);
	}
	return ans;
}
void update(int a,int b,int c,int d,bool f)
{
	for(int i=a;i<=c;++i)
		for(int j=b;j<=d;++j)
			forbid[i][j]=f;
}
int work()
{
	memset(dp,-1,sizeof dp);
	int ans=0;
	for(int i=1;i<=n;++i)
		for(int j=1;j<=n;++j)
			if(!forbid[i][j])ans=std::max(ans,src(i,j));
	return ans;
}
int main()
{
	//freopen("1.in","r",stdin);
	scanf("%d",&n);
	for(int i=1;i<=n;++i)
		for(int j=1;j<=n;++j)
			scanf("%d",&mat[i][j]);
	scanf("%d",&m);
	char s[5];
	while(m--)
	{
		scanf("%s",s);
		int a,b,c,d;
		switch(s[0])
		{
			case 'C':scanf("%d%d%d",&a,&b,&c);
					 mat[a][b]=c;
					 break;
			case 'S':scanf("%d%d%d%d",&a,&b,&c,&d);
					 update(a,b,c,d,1);
					 break;
			case 'B':scanf("%d%d%d%d",&a,&b,&c,&d);
					 update(a,b,c,d,0);
					 break;
			default :printf("%d\n",work());
		}
	}
	return 0;
}
