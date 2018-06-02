#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
const int MAXSTATE=1000000;
const int MAXHASHSIZE=10003;
typedef int State[9];
const State goal={1,2,3,8,0,4,7,6,5};
State st[MAXSTATE];
int dist[MAXSTATE],head[MAXHASHSIZE],nxt[MAXSTATE];
int dx[]={0,1,0,-1};
int dy[]={1,0,-1,0};
void init_lookup_table()
{
	memset(head,0,sizeof(head));
}

int hashv(State &s)
{
	int v=0;
	for(int i=0;i<9;++i) v=v*10+s[i];
	return v%MAXHASHSIZE;
}
bool try_to_insert(int s)
{
	int h=hashv(st[s]);
	int u=head[h];
	while(u)
	{
		if(memcmp(st[u],st[s],sizeof(st[s]))==0) return 0;
		u=nxt[u];
	}
	nxt[s]=head[h];
	head[h]=s;
	return 1;
}
int bfs()
{
	init_lookup_table();
	int front=1,rear=2;
	while(front<rear)
	{
		State &s=st[front];
		if(memcmp(s,goal,sizeof(s))==0) return front;
		int z;
		for(z=0;z<9;++z) if(!s[z]) break;
		int x=z/3,y=z%3;
		for(int i=0;i<4;++i)
		{
			int nx=x+dx[i],ny=y+dy[i];
			if(nx>=0 && nx<3 && ny>=0 && ny<3)
			{
				int nz=nx*3+ny;
				State &t=st[rear];
				memcpy(&t,&s,sizeof(t));
				t[nz]=s[z];
				t[z]=s[nz];
				dist[rear]=dist[front]+1;
				if(try_to_insert(rear)) ++rear;
			}
		}
		++front;
	}
	return 0;
}
int main()
{
//	freopen("1.in","r",stdin);
	char s[15];
	cin>>s;
	for(int i=0;i<9;++i) st[1][i]=s[i]-'0';
	int ans=bfs();
	if(ans>0) cout<<dist[ans]<<endl;
	else cout<<"-1"<<endl;
	return 0;
}
