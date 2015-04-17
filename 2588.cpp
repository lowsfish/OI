#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
const int MAXN=100000+5;
const int INF=~0U>>1;
const int BUFFER_SIZE=10000;
const int MAXLOG=20;
struct Tree{
	Tree* pl,*pr;
	int l,r,sum;
	Tree* set(int _l,int _r,Tree* _pl,Tree* _pr)
	{
		l=_l;r=_r;pl=_pl;pr=_pr;
		sum=pl->sum+pr->sum;
		return this;
	}
	Tree* set(int _l,int _r,int all);
	Tree* add(int pos,int ad);
};
Tree* buffer=0,*cur;
inline Tree* get()
{
	if(!buffer || cur-buffer==BUFFER_SIZE)
		buffer=new Tree[BUFFER_SIZE],cur=buffer;
	return cur++;
}
Tree* Tree::set(int _l,int _r,int all)
{
	l=_l;r=_r;
	if(l+1==r) sum=all;
	else
	{
		int m=(l+r)>>1;
		pl=get()->set(l,m,all);
		pr=get()->set(m,r,all);
		sum=pl->sum+pr->sum;
	}
	return this;
}
Tree* Tree::add(int pos,int ad)
{
	if(l+1==r) return get()->set(l,r,sum+ad);
	int m=(l+r)>>1;
	if(pos<m) return get()->set(l,r,pl->add(pos,ad),pr);
	else return get()->set(l,r,pl,pr->add(pos,ad));
}
Tree* pt[MAXN];
int anc[MAXN][MAXLOG];
int dep[MAXN];
int w[MAXN],sortw[MAXN];
std::vector<int> G[MAXN];
typedef std::vector<int>::iterator vit;
void dfs(int u,Tree* t)
{
	t=t->add(w[u],1);
	pt[u]=t;
	for(int i=1;i<MAXLOG;++i)
	{
		int a=anc[u][i-1];
		if(a==-1) anc[u][i]=-1;
		else anc[u][i]=anc[a][i-1];
	}
	for(vit e=G[u].begin();e!=G[u].end();++e) if(*e!=anc[u][0])
	{
		anc[*e][0]=u;
		dep[*e]=dep[u]+1;
		dfs(*e,t);
	}
}
int get_lca(int u,int v)
{
	if(dep[u]<dep[v]) std::swap(u,v);
	int step=dep[u]-dep[v];
	for(int i=MAXLOG-1;i>=0;--i) if(step&(1<<i)) u=anc[u][i];
	if(u==v) return u;
	for(int i=MAXLOG-1;i>=0;--i)
	{
		int tu=anc[u][i],tv=anc[v][i];
		if(tu!=tv) u=tu,v=tv;
	}
	return anc[u][0];
}
int n,m;
int query(int u,int v,int k)
{
	int lca=get_lca(u,v);
	Tree* tu=pt[u],*tv=pt[v],*tl=pt[lca];
	while(tu->l +1 < tu->r)
	{
		int sum=tu->pl->sum + tv->pl->sum - 2*tl->pl->sum+
						(w[lca]>=tu->pl->l && w[lca]<tu->pl->r);
		if(sum<=k) k-=sum,tu=tu->pr,tv=tv->pr,tl=tl->pr;
		else tu=tu->pl,tv=tv->pl,tl=tl->pl;
	}
	return sortw[tu->l];
}
int main()
{
	//freopen("1.in","r",stdin);
	scanf("%d%d",&n,&m);
	for(int i=0;i<n;++i) scanf("%d",w+i),sortw[i]=w[i];
	for(int i=0;i<n-1;++i)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		--u;--v;
		G[u].push_back(v);
		G[v].push_back(u);
	}
	std::sort(sortw,sortw+n);
	int nn=std::unique(sortw,sortw+n)-sortw;
	for(int i=0;i<n;++i) w[i]=std::lower_bound(sortw,sortw+nn,w[i])-sortw;
	anc[0][0]=-1;
	dep[0]=0;
	dfs(0,get()->set(0,nn,0));
	int last=0;
	while(m--)
	{
		int u,v,k;
		scanf("%d%d%d",&u,&v,&k);
		u^=last;
		--u;--v;--k;
		printf("%d",last=query(u,v,k));
		if(m) putchar(10);
	}
	return 0;
}

