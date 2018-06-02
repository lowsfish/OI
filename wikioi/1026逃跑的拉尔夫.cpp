#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
using namespace std;
const int MAXSZ=50+15;
const int MAXN=1000+10;
char mat[MAXSZ][MAXSZ];
char s[MAXN][10];
bool vis[MAXSZ][MAXSZ][MAXN];
int r,c,n,sx,sy;

struct Node{
	int x,y,dir;
	Node() {}
	Node(int x,int y,int dir):x(x),y(y),dir(dir) {} 
};

void input()
{
	scanf("%d%d",&r,&c);
	cin.get();
	for(int i=0;i<r;++i)
	{
		scanf("%s",mat[i]);
		for(int j=0;j<c;++j)
		{
			if(mat[i][j]=='*')
			{
				sx=i;sy=j;
			}
		}
	}
	scanf("%d",&n);
	for(int i=1;i<=n;++i)
	{
		scanf("%s",s[i]);
	}
}

void bfs()
{
	mat[sx][sy]='.';
	queue<Node>que;
	que.push(Node(sx,sy,0));
	while(!que.empty())
	{
		Node node=que.front();que.pop();
		int nd=node.dir+1,x=node.x,y=node.y;
		if(nd>n)
		{
			mat[x][y]='*';
			continue;
		}
		switch(s[nd][0])
		{
			case 'N':
				--x;
				for(;x>=0;--x)
				{
					if(mat[x][y]=='X') break;
					if(vis[x][y][nd]) continue;
					que.push(Node(x,y,nd));
					vis[x][y][nd]=1;
				}
				break;
			case 'S':
				++x;
				for(;x<r;++x)
				{
					if(mat[x][y]=='X') break;
					if(vis[x][y][nd]) continue;
					que.push(Node(x,y,nd));
					vis[x][y][nd]=1;
				}
				break;
			case 'W':
				--y;
				for(;y>=0;--y)
				{
					if(mat[x][y]=='X') break;
					if(vis[x][y][nd]) continue;
					que.push(Node(x,y,nd));
					vis[x][y][nd]=1;
				}
				break;
			case 'E':
				++y;
				for(;y<c;++y)
				{
					if(mat[x][y]=='X') break;
					if(vis[x][y][nd]) continue;
					que.push(Node(x,y,nd));
					vis[x][y][nd]=1;
				}
				break;
		}
	}
}

void print()
{

	for(int i=0;i<r;++i)
		printf("%s\n",mat[i]);
}

int main()
{
	freopen("1.in","r",stdin);
	input();
	bfs();
	print();
	return 0;
}
