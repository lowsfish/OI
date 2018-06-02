#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#include<queue>
using namespace std;
const int MAXV=100+10;
const int INF=(1<<29)-1;
int d[MAXV],n,num[MAXV];
bool inq[MAXV];
vector<int> G[MAXV];

void input()
{
	scanf("%d",&n);
	for(int i=1;i<=n;++i)
	{
		int u,v;
		scanf("%d%d%d",num+i,&u,&v);
		if(u)
		{
			G[i].push_back(u);
			G[u].push_back(i);
		}
		if(v)
		{
			G[i].push_back(v);
			G[v].push_back(i);
		}
	}
}

void spfa(int s)
{
	for(int i=0;i<MAXV;++i) d[i]=i==s?0:INF;
	queue<int> que;
	que.push(s);
	inq[s]=1;
	while(!que.empty())
	{
		int x=que.front();que.pop();
		inq[x]=0;
		for(int e=0;e<G[x].size();++e)
		{
			int t=G[x][e];
			if(d[t]>d[x]+1)
			{
				d[t]=d[x]+1;
				if(!inq[t])
				{
					que.push(t);
					inq[t]=1;
				}
			}
		}
	}
}

int main()
{
//	freopen("1.in","r",stdin);
	input();
	int ans=INF;
	for(int i=1;i<=n;++i)
	{
		spfa(i);
		int t=0;
		for(int j=1;j<=n;++j) t+=d[j]*num[j];
		ans=min(ans,t);
	}
	printf("%d\n",ans);
	return 0;
}
