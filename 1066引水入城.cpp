#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<queue>
using namespace std;
typedef pair<int,int> P;
const int MAXN=500+10;
P seg[MAXN];
int mat[MAXN][MAXN];
bool vis[MAXN][MAXN],vis2[MAXN];
int n,m;
int dx[]={0,1,0,-1},dy[]={-1,0,1,0};
const int INF=1<<28;
void init()
{
	for(int i=0;i<m;++i) seg[i].first=INF,seg[i].second=-1;
}

void dfs(int p,int x,int y)
{
	vis[x][y]=1;
	if(x==n-1) 
	{
        vis2[y]=1;
		seg[p].first=min(y,seg[p].first);
		seg[p].second=max(y,seg[p].second);
	}
	int h=mat[x][y];
	for(int i=0;i<4;++i)
	{
		int nx=x+dx[i],ny=y+dy[i];
		if(nx>=0 && nx<n && ny>=0 && ny<m && mat[nx][ny]<h && !vis[nx][ny]) dfs(p,nx,ny);
	}
}


int main()
{
	//freopen("1.in","r",stdin);
	scanf("%d%d",&n,&m);
	for(int i=0;i<n;++i)
		for(int j=0;j<m;++j)
			scanf("%d",&mat[i][j]);
	init();
	for(int i=0;i<m;++i) if(mat[0][i]>=((i==0)?-1:mat[0][i-1]) && mat[0][i]>=((i==m-1)?-1:mat[0][i+1])) 
	{
		memset(vis,0,sizeof(vis));
		dfs(i,0,i);
	}
	int cnt=0;
	for(int i=0;i<m;++i)
	{
		if(!vis2[i]) ++cnt;
	}
	if(cnt>0)
	{
		printf("0\n%d\n",cnt);
		return 0;
	}
    sort(seg,seg+m);
	int i,s=0,t=m-1,ans=0;
	for(i=0;i<m && seg[i].first==0;++i);
	s=seg[i-1].second+1;
	++ans;
	while(s<=t)
	{
		for(;i<m && seg[i].first<=s;++i);
		s=seg[i-1].second+1;
		++ans;
	}
	printf("1\n%d\n",ans);
	return 0;
}
