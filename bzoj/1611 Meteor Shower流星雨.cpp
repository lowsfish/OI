#include<cstdio>
#include<queue>
#include<algorithm>
const int INF=~0U>>1;
const int MAXN=300+10;
int mat[MAXN][MAXN];
int ti[MAXN][MAXN];
int dx[]={-1,0,1,0},dy[]={0,1,0,-1};
inline void update(int x,int y,int t)
{
	ti[x][y]=std::min(ti[x][y],t);
	for(int i=0;i<4;++i)
	{
		int nx=x+dx[i],ny=y+dy[i];
		if(nx>=0 && ny>=0)
				ti[nx][ny]=std::min(ti[nx][ny],t);
	}
}
typedef std::pair<int,int>P;
#define fr first
#define sc second
int bfs()
{
	std::queue<P> que;
	que.push(P(0,0));
	mat[0][0]=0;
	while(!que.empty())
	{
		P p=que.front();que.pop();
		for(int i=0;i<4;++i)
		{
			int nx=p.fr+dx[i],ny=p.sc+dy[i];
			if(nx>=0 && ny>=0 && mat[nx][ny]==INF && ti[nx][ny]>mat[p.fr][p.sc]+1)
			{
				if(ti[nx][ny]==INF) return mat[p.fr][p.sc]+1;
				que.push(P(nx,ny));
				mat[nx][ny]=mat[p.fr][p.sc]+1;
			}
		}
	}
	return -1;
}
int n;
int main()
{
	scanf("%d",&n);
	for(int i=0;i<MAXN;++i)
			for(int j=0;j<MAXN;++j)
					mat[i][j]=ti[i][j]=INF;
	while(n--)
	{
		int x,y,t;
		scanf("%d%d%d",&x,&y,&t);
		update(x,y,t);
	}
	printf("%d\n",bfs());
	return 0;
}
