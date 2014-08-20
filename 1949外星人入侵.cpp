#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#include<queue>
using namespace std;
const int MAXV=1e4+10;
const int INF=(1<<29)-1;
struct edge{
	int to,cost;
	edge() {}
	edge(int to,int cost):to(to),cost(cost) {}
};

vector<edge> G[MAXV];
int N,M,A,K,cnt=0;
int b[MAXV];
int d[MAXV];
bool inq[MAXV];

void input()
{
	scanf("%d%d%d%d",&N,&M,&A,&K);
	for(int i=0;i<M;++i)
	{
		int u,v,cost;
		scanf("%d%d%d",&u,&v,&cost);
		G[u].push_back(edge(v,cost));
		G[v].push_back(edge(u,cost));
	}
	for(int i=0;i<A;++i)
	{
		scanf("%d",b+i);
	}
	for(int i=0;i<=N;++i)
	{
		d[i]=INF;
	}
	memset(inq,0,sizeof(inq));
}

void SPFA(int s)
{
	if(d[s]>=K) ++cnt;
	d[s]=0;
	queue<int>que;
	que.push(s);
	inq[s]=1;
	while(!que.empty())
	{
		int x=que.front();que.pop();
		inq[x]=0;
		for(int e=0;e<G[x].size();++e)
		{
			edge es=G[x][e];
			if(d[es.to]>d[x]+es.cost)
			{
				if(d[es.to]>=K && d[x]+es.cost<K) ++cnt;
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
	freopen("1.in","r",stdin);
	input();
	for(int i=0;i<A;++i)
	{
		SPFA(b[i]);
		printf("%d\n",N-cnt);
	}
	return 0;
}
