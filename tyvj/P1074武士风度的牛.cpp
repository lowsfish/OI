#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#define MAXSZ 160
using namespace std;
typedef pair<int,int> P;
char mat[MAXSZ][MAXSZ];
bool vis[MAXSZ][MAXSZ]={0};
int dx[]={-2,-1,1,2,2,1,-1,-2},dy[]={1,2,2,1,-1,-2,-2,-1};
int x,y,sx,sy,ex,ey;
int dist[MAXSZ][MAXSZ];
void srch()
{
	for(int i=0;i<y;++i)
		for(int j=0;j<x;++j)
		{
			if(mat[i][j]=='H') {ex=j;ey=i;}
			if(mat[i][j]=='K') {sx=j;sy=i;}
		}
}

int bfs()
{
	queue<P> que;
	que.push(P(sy,sx));
	while(!que.empty())
	{
		P p=que.front();que.pop();
		for(int i=0;i<8;++i)
		{
			int nx=p.second+dx[i],ny=p.first+dy[i];
			if(nx>=0 && nx<x && ny>=0 && ny<y && !vis[ny][nx] && mat[ny][nx]!='*')
			{
				vis[ny][nx]=1;
				dist[ny][nx]=dist[p.first][p.second]+1;
				if(ny==ey && nx==ex) return dist[ny][nx];
				que.push(P(ny,nx));
			}
		}
	}
	return -1;
}

int main()
{
//	freopen("1.in","r",stdin);
	cin>>x>>y;
	cin.get();
	for(int i=0;i<y;++i) cin.getline(mat[i],MAXSZ);
	srch();
//	cout<<sx<<endl<<sy<<endl<<ex<<endl<<ey<<endl;
	cout<<bfs();
	return 0;
}

