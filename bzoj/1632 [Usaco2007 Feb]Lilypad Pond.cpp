#include<cstdio>
#include<queue>
#include<cstring>
#include<algorithm>
#define xx first
#define yy second
const int MAXN=30+5;
const int INF=~0U>>2;
typedef long long LL;
int mat[MAXN][MAXN],dis[MAXN][MAXN],add[MAXN][MAXN];
LL num[MAXN][MAXN];
bool inq[MAXN][MAXN];
int dx[]={-2,-1,1,2,2,1,-1,-2},dy[]={1,2,2,1,-1,-2,-2,-1};
int n,m;
int sx,sy,ex,ey;
typedef std::pair<int,int> P;
void bfs()
{
	std::queue<P> que;
	que.push(P(sx,sy));
	inq[sx][sy]=1;num[sx][sy]=1;
	while(!que.empty())
	{
		P p=que.front();que.pop();inq[p.xx][p.yy]=0;
		for(int i=0;i<8;++i)
		{
			int nx=p.xx+dx[i],ny=p.yy+dy[i];
			if(nx>=0 && nx<n && ny>=0 && ny<m && mat[nx][ny]!=2)
			{
				int ad=add[p.xx][p.yy]+(mat[nx][ny]==0),d=dis[p.xx][p.yy]+1;
				if(ad>add[nx][ny]) continue;
				if(ad<add[nx][ny])
				{
					add[nx][ny]=ad;
					dis[nx][ny]=dis[p.xx][p.yy]+1;
					num[nx][ny]=num[p.xx][p.yy];
					if(!inq[nx][ny]) que.push(P(nx,ny)),inq[nx][ny]=1;
				}
				else
				{
					if(dis[p.xx][p.yy]+1>dis[nx][ny]) continue;
					if(dis[p.xx][p.yy]+1<dis[nx][ny])
					{
						dis[nx][ny]=dis[p.xx][p.yy]+1;
						num[nx][ny]=num[p.xx][p.yy];
					}
					else
						num[nx][ny]+=num[p.xx][p.yy];
					if(!inq[nx][ny]) que.push(P(nx,ny)),inq[nx][ny]=1;
				}
			}
		}
	}
}
int main()
{
	freopen("1.in","r",stdin);
	scanf("%d%d",&n,&m);
	for(int i=0;i<n;++i)
		for(int j=0;j<m;++j)
		{
			scanf("%d",&mat[i][j]);
			if(mat[i][j]==3) sx=i,sy=j;
			else if(mat[i][j]==4) ex=i,ey=j;
		}
	std::fill(dis[0],&dis[n-1][m-1]+1,INF);
	std::fill(add[0],&add[n-1][m-1]+1,INF);
	memset(inq,0,sizeof inq);
	num[sx][sy]=1;add[sx][sy]=0;dis[sx][sy]=0;
	bfs();
	if(add[ex][ey]==INF) printf("-1\n");
	else printf("%d\n%d\n%lld\n",add[ex][ey],dis[ex][ey],num[ex][ey]);
	return 0;
}
