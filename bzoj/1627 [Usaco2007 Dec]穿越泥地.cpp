#include<cstdio>
#include<queue>
#include<algorithm>
const int MAXN=1000+5;
const int INF=~0U>>2;
bool mat[MAXN][MAXN];
int dist[MAXN][MAXN];
int x,y,n;
#define X first
#define Y second
typedef std::pair<int,int> P;
int dx[]={0,-1,0,1},dy[]={1,0,-1,0};
int bfs()
{
	std::queue<P> que;
	que.push(P(501,501));
	dist[501][501]=0;
	while(!que.empty())
	{
		P p=que.front();que.pop();
		for(int i=0;i<4;++i)
		{
			int nx=p.X+dx[i],ny=p.Y+dy[i];
			if(nx>=0 && nx<MAXN && ny>=0 && ny<MAXN && !mat[nx][ny] && dist[nx][ny]==INF)
			{
				dist[nx][ny]=dist[p.X][p.Y]+1;
				que.push(P(nx,ny));
				if(nx==x && ny==y) return dist[x][y];
			}
		}
	}
}
int main()
{
	for(int i=0;i<MAXN;++i)
		for(int j=0;j<MAXN;++j) dist[i][j]=INF;
	scanf("%d%d%d",&x,&y,&n);
	x+=501;y+=501;
	for(int i=0;i<n;++i)
	{
		int a,b;
		scanf("%d%d",&a,&b);
		a+=501;b+=501;
		mat[a][b]=1;
	}
	printf("%d\n",bfs());
	return 0;
}
