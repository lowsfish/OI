/*
ID: rainbow16
LANG: C++
TASK: maze1
*/
#include<cstdio>
#include<algorithm>
#include<queue>
#include<iostream>
#include<cstring>
const int MAXN=200+10;
typedef std::pair<int,int> P;
P en[2];
char mat[MAXN][MAXN];
int w,h;
void srcen()
{
	int flag=0;
	for(int i=0;i<=(w<<1);++i)
	{
		if(mat[0][i]==' ') en[flag++]=P(0,i);
		if(mat[2*h][i]==' ') en[flag++]=P(2*h,i);
	}
	for(int i=0;i<=(h<<1);++i)
	{
		if(mat[i][0]==' ') en[flag++]=P(i,0);
		if(mat[i][w*2]==' ') en[flag++]=P(i,w*2);
	}
}
int d[MAXN][MAXN];
#define fi first
#define se second
int dx[]={-1,0,1,0},dy[]={0,1,0,-1};
int maxd=-1;
void bfs()
{
	memset(d,-1,sizeof(d));
	std::queue<P> que;
	d[en[0].fi][en[0].se]=d[en[1].fi][en[1].se]=0;
	que.push(en[0]);que.push(en[1]);
	while(!que.empty())
	{
		P p=que.front();que.pop();
		for(int i=0;i<4;++i)
		{
			int nx=p.fi+dx[i],ny=p.se+dy[i];
			if(nx>=0 && nx<=2*h && ny>=0 && ny<=w*2 && mat[nx][ny]==' ' && d[nx][ny]==-1)
			{
				d[nx][ny]=d[p.fi][p.se]+1;
				maxd=std::max(maxd,d[nx][ny]);
				que.push(P(nx,ny));
			}
		}
	}
}
int main()
{
	freopen("maze1.in","r",stdin);
	freopen("maze1.out","w",stdout);
	scanf("%d%d",&w,&h);
	getchar();
	for(int i=0;i<=(h<<1);++i)
		std::cin.getline(mat[i],MAXN);
	srcen();
	bfs();
	printf("%d\n",maxd+1>>1);
	return 0;
}
