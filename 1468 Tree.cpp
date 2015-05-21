#include<cstdio>
#include<vector>
#include<algorithm>
#include<cstring>
#define rep(i,n) for(int i=0;i<n;++i)
const int MAXN=40000+5;
const int INF=~0U>>1;
typedef std::pair<int,int> P;
int n,k;
struct Edge{
	int v,c;
	Edge(int _v,int _c):v(_v),c(_c) {}
};
typedef std::vector<Edge>::iterator it;
std::vector<Edge> G[MAXN];
int size[MAXN],centroid[MAXN];
int ans;
int getsz(int u,int p)
{
	int c=1;
	for(it e=G[u].begin();e!=G[u].end();++e) if(e->v!=p && !centroid[e->v])
		c+=getsz(e->v,u);
	return size[u]=c;
}
P search_centroid(int u,int p,int t)
{
	P res=P(INF,-1);
	int s=1,m=0;
	for(it e=G[u].begin();e!=G[u].end();++e) if(e->v!=p && !centroid[e->v])
	{
		res=std::min(res,search_centroid(e->v,u,t));
		m=std::max(m,size[e->v]);
		s+=size[e->v];
	}
	m=std::max(m,t-s);
	return res=std::min(res,P(m,u));
}
void get_dist(int u,int p,int d,std::vector<int>& ds)
{
	ds.push_back(d);
	for(it e=G[u].begin();e!=G[u].end();++e) if(e->v!=p && !centroid[e->v])
		get_dist(e->v,u,d+e->c,ds);
}
int calculate(std::vector<int>& ds)
{
	int res=0;
	std::sort(ds.begin(),ds.end());
	int i=0,j=ds.size()-1;
	while(i<j)
	{
		if(ds[i]+ds[j]<=k) {res+=j-i;++i;}
		else --j;
	}
	return res;
}
void solve_subproblem(int u)
{
	getsz(u,-1);
	int s=search_centroid(u,-1,size[u]).second;
	centroid[s]=1;
	for(it e=G[s].begin();e!=G[s].end();++e) if(!centroid[e->v])
		solve_subproblem(e->v);
	std::vector<int> ds;
	ds.push_back(0);
	for(it e=G[s].begin();e!=G[s].end();++e) if(!centroid[e->v])
	{
		std::vector<int> tds;
		get_dist(e->v,s,e->c,tds);
		ans-=calculate(tds);
		ds.insert(ds.end(),tds.begin(),tds.end());
	}
	ans+=calculate(ds);
	centroid[s]=0;
}
void init()
{
	rep(i,n) G[i+1].clear();
	memset(centroid,0,sizeof(centroid));
	ans=0;
}
int main()
{
	scanf("%d",&n);
	init();
	rep(i,n-1)
	{
		int u,v,c;
		scanf("%d%d%d",&u,&v,&c);
	//	--u;--v;
		G[u].push_back(Edge(v,c));
		G[v].push_back(Edge(u,c));
	}
	scanf("%d",&k);
	solve_subproblem(1);
	printf("%d\n",ans);
	return 0;
}
