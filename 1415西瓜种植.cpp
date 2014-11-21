#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#include<vector>
using namespace std;
const int MAXN=5000+10;
int n,m;
int d[MAXN];
bool inq[MAXN];
const int INF=(1<<29)-1;

struct edge{
	int to,cost;
	edge(){}
	edge(int to,int cost):to(to),cost(cost) {}
};
vector<edge> G[MAXN];

void input()
{
	for(int i=0;i<=n+1;++i) G[i].clear();
	for(int i=0;i<m;++i)
	{
		int b,e,t;
		scanf("%d%d%d",&b,&e,&t);
		++e;
		G[b].push_back(edge(e,t));
	}
	for(int i=1;i<=n+1;++i)
	{
		G[i].push_back(edge(i-1,-1));	//d[i-1]-d[i]>=-1
		G[i-1].push_back(edge(i,0));	//d[i]-d[i-1]>=0
	}
}

void spfa(int s)
{
	for(int i=0;i<MAXN;++i) d[i]=i==s?0:-INF;	//求最长路
	queue<int>que;
	que.push(s);
	memset(inq,0,sizeof(inq));
	inq[s]=1;
	while(!que.empty())
	{
		int x=que.front();que.pop();
		inq[x]=0;
		for(int e=0;e<G[x].size();++e)
		{
			edge es=G[x][e];
			if(d[es.to]<d[x]+es.cost)
			{
				d[es.to]=d[x]+es.cost;
				if(!inq[es.to])
				{
					que.push(es.to);
					inq[es.to]=1;
				}
			}
		}
	}
}

int main()
{
	//freopen("1.in","r",stdin);
	while(scanf("%d%d",&n,&m)!=EOF)
	{
		input();
		spfa(0);
		printf("%d\n",d[n+1]);
	}
	return 0;
}
