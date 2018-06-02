#include<iostream>
#include<cstdio>
#define M 105
using namespace std;
int temp[M][M]={0};
int mat[M][M],dx[4]={0,-1,0,1},dy[4]={-1,0,1,0};
int r,c;
int dfs(int x,int y)
{
	if(temp[x][y]!=0) return temp[x][y];
	int ans=1;
	for(int i=0;i<4;++i)
	{
		int nx=x+dx[i],ny=y+dy[i];
		if(nx>=0 && nx<r && ny>=0 && ny<c && mat[nx][ny]<mat[x][y])
			ans=max(ans,dfs(nx,ny)+1);
	}
	return temp[x][y]=ans;
}
int main()
{
	ios::sync_with_stdio(false);
	freopen("1.in","r",stdin);
	int i,j,ans=0;
	cin>>r>>c;
	for(i=0;i<r;++i)
		for(j=0;j<c;++j)
			cin>>mat[i][j];
	for(i=0;i<r;++i)
		for(j=0;j<c;++j)
			ans=max(ans,dfs(i,j));
	cout<<ans<<endl;
}

