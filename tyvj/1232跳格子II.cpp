#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#include<queue>
using namespace std;
const int MAXV=500*500+10;
const int MAXN=500+10;

struct Edge{
	int to,cost;
	Edge() {}
	Edge(int to,int cost):to(to),cost(cost) {}
};

vector<Edge> G[MAXV];
bool inq[MAXV];
char mat[MAXN][MAXN];
int n,m;
int sx,sy,ex,ey;
int dx[]={-1,0,1,0},dy[]={0,-1,0,1};
int d[MAXV];

void input_setup()
{
	scanf("%d%d",&n,&m);
	for(int i=0;i<n;++i)
	{
		scanf("%s",mat[i]);
	}
	scanf("%d%d%d%d",&sx,&sy,&ex,&ey);
	--sx;--sy;--ex;--ey;
	for(int i=0;i<n;++i)
		for(int j=0;j<m;++j)
		{
			int t=i*m+j;
			for(int k=0;k<4;++k)
			{
				int nx=i+dx[k],ny=j+dy[k];
				if(nx>=0 && nx<n && ny>=0 && ny<m)
				{
					int t2=nx*m+ny;
					G[t].push_back(Edge(t2,mat[i][j]==mat[nx][ny]?1:2));
				}
			}

		}
}

const int INF=(1<<29)-1;

void SPFA(int s)
{
	queue<int>que;
	for(int i=0;i<=n*m;++i) d[i]=i==s?0:INF;
	que.push(s);
	while(!que.empty())
	{
		int x=que.front();que.pop();
		inq[x]=0;
		for(int e=0;e<G[x].size();++e)
		{
			Edge es=G[x][e];
			if(d[es.to]>d[x]+es.cost)
			{
				d[es.to]=d[x]+es.cost;
				if(!inq[es.to])
				{
					inq[es.to]=1;
					que.push(es.to);
				}
			}
		}
	}
}

int main()
{
	//freopen("1.in","r",stdin);
	input_setup();
	SPFA(sx*m+sy);
	printf("%d\n",d[ex*m+ey]);
	return 0;
}
