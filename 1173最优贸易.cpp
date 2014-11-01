#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#include<queue>
using namespace std;
const int MAXN=100000+10;
const int INF=1<<28;
vector<int> G[2][MAXN];		//G[0]是正向图，G[1]是反向图
int cost[MAXN];
int mincost[MAXN],maxcost[MAXN];
int n,m;
bool inq[MAXN];
void init()
{
	for(int i=1;i<=n;++i) mincost[i]=i==1?cost[1]:INF,
						maxcost[i]=i==n?cost[n]:-1;
}

void SPFA(int s)
{
	memset(inq,0,sizeof(inq));
	bool flag=0;
	if(s==n) flag=1;
	queue<int> que;
	que.push(s);
	while(!que.empty())
	{
		int x=que.front();que.pop();
		inq[x]=0;
		for(int i=0;i<G[flag][x].size();++i)
		{
			int e=G[flag][x][i];
			if(!flag)
			{
				if(mincost[e]>min(mincost[x],cost[e]))
				{
					mincost[e]=min(mincost[x],cost[e]);
					if(!inq[e])
					{
						que.push(e);
						inq[e]=1;
					}
				}
			}
			else
			{
				if(maxcost[e]<max(maxcost[x],cost[e]))
				{
					maxcost[e]=max(maxcost[x],cost[e]);
					if(!inq[e])
					{
						que.push(e);
						inq[e]=1;
					}
				}
			}
		}
	}
}
int main()
{
	freopen("1.in","r",stdin);
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i) scanf("%d",cost+i);
	for(int i=0;i<m;++i)
	{
		int x,y,z;
		scanf("%d%d%d",&x,&y,&z);
		G[0][x].push_back(y);
		G[1][y].push_back(x);
		if(z==2)
		{
			G[0][y].push_back(x);
			G[1][x].push_back(y);
		}
	}
	init();
	SPFA(1);
	SPFA(n);
	int ans=0;
	for(int i=1;i<=n;++i)
	{
		ans=max(ans,maxcost[i]-mincost[i]);
	}
	printf("%d\n",ans);
	return 0;
}
