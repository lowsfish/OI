#include<iostream>
#include<cstdio>
#include<queue>
#include<cstring>
#define M 190
using namespace std;
typedef pair<int,int> P;
const int INF=(1<<29);
int m,n;
char tu[M][M];
int ans[M][M],dx[4]={0,-1,0,1},dy[4]={-1,0,1,0};
/*int bfs(P s)
{
	bool used[M][M];
	int temp[M][M];
	memset(temp,-1,sizeof(temp));
	memset(used,0,sizeof(used));
	temp[s.first][s.second]=0;
	used[s.first][s.second]=1;
	queue<P> que;
	que.push(s);
	while(que.size())
	{
		P p=que.front();que.pop();
		//if(tu[p.first][p.second]=='1') return temp[p.first][p.second];
		for(int i=0;i<4;++i)
		{
			int nx=p.first+dx[i],ny=p.second+dy[i];
			if(tu[nx][ny]=='1') return temp[p.first][p.second]+1;
			if(nx>=0 && nx<m && ny>=0 && ny<n && !used[nx][ny] && tu[nx][ny]=='0')
			{
				que.push(make_pair(nx,ny));
				temp[nx][ny]=temp[p.first][p.second]+1;
				used[nx][ny]=1;
			}
		}		
	}
}
*/

void bfs()
{
	queue<P> que;
	for(int i=0;i<m;++i)
		for(int j=0;j<n;++j)
			if(tu[i][j]=='1') que.push(make_pair(i,j));
	while(que.size())
	{
		P p=que.front();que.pop();
		for(int i=0;i<4;++i)
		{
			int nx=p.first+dx[i],ny=p.second+dy[i];
			if(nx>=0 && nx<m && ny>=0 && ny<n && ans[nx][ny]==INF)
			{
				ans[nx][ny]=ans[p.first][p.second]+1;
				que.push(make_pair(nx,ny));
			}
		}
	}
}
int main()
{
	freopen("1.in","r",stdin);
	int i,j;
	cin>>m>>n;
	for(i=0;i<m;++i)
		{
			cin>>tu[i];
		}
	for(i=0;i<m;++i)
		for(j=0;j<n;++j)
		{
			if(tu[i][j]=='0') 
				ans[i][j]=INF;
			else 
				ans[i][j]=0;
		}
	bfs();
	for(i=0;i<m;++i)
	{
		for(j=0;j<n;++j)
		{
			cout<<ans[i][j];
			//cout<<tu[i][j];
			if(j!=n-1) cout<<' ';
		}
		cout<<endl;
	}
	return 0;
}
