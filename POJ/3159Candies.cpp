#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#include<vector>
#include<stack>
using namespace std;
const int MAXN=30000+10;
const int MAXE=150000+10;
const int INF=(1<<29)-1;
int n,m;
bool inq[MAXN];
int d[MAXN];
int first[MAXN],u[MAXE],v[MAXE],cost[MAXE],next[MAXE];
void input()
{
	scanf("%d%d",&n,&m);
	memset(first,-1,sizeof(first));
	for(int i=0;i<m;++i)
	{
		int a,b,c;
		scanf("%d%d%d",u+i,v+i,cost+i);
		next[i]=first[u[i]];
		first[u[i]]=i;
	}
}

void spfa(int s)
{
	for(int i=0;i<=n;++i) d[i]=i==s?0:INF;
	stack<int>st;
	st.push(s);
	while(!st.empty())
	{
		int x=st.top();st.pop();
		inq[x]=0;
		for(int e=first[x];e!=-1;e=next[e])
		{
			if(d[v[e]]>d[u[e]]+cost[e])
			{
				d[v[e]]=d[u[e]]+cost[e];
				if(!inq[v[e]])
				{
					inq[v[e]]=1;
					st.push(v[e]);
				}
			}
		}
	}
}
/*typedef pair<int,int>P;
void dijkstra(int s)
{
	priority_queue<P,vector<P>,greater<P> >que;
	for(int i=0;i<=n;++i) d[i]=i==s?0:INF;
	que.push(P(0,s));
	while(!que.empty())
	{
		P p=que.top();que.pop();
		int v=p.second;
		if(d[v]<p.first) continue;
		for(int i=0;i<G[v].size();++i)
		{
			edge e=G[v][i];
			if(d[e.to]>d[v]+e.cost)
			{
				d[e.to]=d[v]+e.cost;
				que.push(P(d[e.to],e.to));
			}
		}
	}
}*/
int main()
{
	freopen("1.in","r",stdin);
	input();
	spfa(1);
	printf("%d\n",d[n]);
	return 0;
}
