#include<cstdio>
#include<queue>
#include<vector>
struct Edge{
	int v,c;
	Edge(int v,int c):v(v),c(c) {}
};
const int MAXN=1000+5;
const int INF=~0U>>1;
std::vector<Edge> G[MAXN];
typedef std::vector<Edge>::iterator it;
int d[MAXN];
int n,p,k,mx;
bool inq[MAXN];
int spfa(int m,int s,int t)
{
	std::queue<int> que;
	for(int i=1;i<=n;++i) d[i]=i==s?0:INF;
	inq[s]=1;que.push(s);
	while(!que.empty())
	{
		int x=que.front();que.pop();
		inq[x]=0;
		for(it e=G[x].begin();e!=G[x].end();++e)
		{
			bool t=m<e->c;
			if(d[e->v]>d[x]+t)
			{
				d[e->v]=d[x]+t;
				if(!inq[e->v]) inq[e->v]=1,que.push(e->v);
			}
		}
	}
	return d[t];
}
int main()
{
	freopen("1.in","r",stdin);
	scanf("%d%d%d",&n,&p,&k);
	while(p--)
	{
		int u,v,c;
		scanf("%d%d%d",&u,&v,&c);
		G[u].push_back(Edge(v,c));
		G[v].push_back(Edge(u,c));
		mx=std::max(mx,c);
	}
	int l=0,r=mx;
	while(l<r)
	{
		int m=(l+r)>>1;
		if(spfa(m,1,n)<=k) r=m;
		else l=m+1;
	}
	if(spfa(0,1,n)==INF) printf("%d\n",-1);
	else printf("%d\n",r);
	return 0;
}
