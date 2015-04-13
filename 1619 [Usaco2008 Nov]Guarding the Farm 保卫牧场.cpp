#include<cstdio>
#include<algorithm>
const int MAXN=700+5;
int mat[MAXN][MAXN];
int n,m;
bool vis[MAXN][MAXN];
int dx[]={-1,-1,-1,0,1,1,1,0},dy[]={1,0,-1,-1,-1,0,1,1};
void dfs(int x,int y)
{
	vis[x][y]=1;
	for(int i=0;i<8;++i)
	{
		int nx=x+dx[i],ny=y+dy[i];
		if(nx>=0 && ny>=0 && nx<n && ny<m && !vis[nx][ny] && mat[nx][ny]<=mat[x][y])
			dfs(nx,ny);
	}
}
struct Node{
	int x,y,h;
	Node() {}
	Node(int x,int y,int h):x(x),y(y),h(h) {}
	bool operator<(const Node& rhs)const
	{
		return h>rhs.h;
	}
}a[MAXN*MAXN];
int main()
{
	//freopen("1.in","r",stdin);
	scanf("%d%d",&n,&m);
	for(int i=0;i<n;++i)
		for(int j=0;j<m;++j)
		{
			scanf("%d",&mat[i][j]);
			int t=i*m+j;
			a[t]=Node(i,j,mat[i][j]);
		}
	std::sort(a,a+m*n);
	int ans=0;
	for(int i=0;i<m*n;++i) if(!vis[a[i].x][a[i].y])
		dfs(a[i].x,a[i].y),++ans;
	printf("%d\n",ans);
	return 0;
}
