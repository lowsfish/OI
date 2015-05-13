#include<cstdio>
#include<vector>
using std::vector;
typedef vector<int>::iterator vit;
const int MAXN=400000+5;
vector<int> G[MAXN];
int pa[MAXN];
int n,m,k;
int find(int x)
{
	return pa[x]==x?x:pa[x]=find(pa[x]);
}
int tmp;
void unite(int x,int y)
{
	x=find(x);y=find(y);
	if(x==y) return;
	--tmp;
	pa[x]=y;
}
int dest[MAXN];
int ans[MAXN];
bool vis[MAXN];
int main()
{
	freopen("1.in","r",stdin);
	scanf("%d%d",&n,&m);
	for(int i=0;i<n;++i) pa[i]=i;
	for(int i=1;i<=m;++i)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		G[u].push_back(v);
		G[v].push_back(u);
	}
	scanf("%d",&k);
	tmp=n-k;
	for(int i=0;i<k;++i) scanf("%d",dest+i),vis[dest[i]]=1;
	for(int i=0;i<n;++i) if(!vis[i])
	{
		for(vit e=G[i].begin();e!=G[i].end();++e) if(!vis[*e])
			unite(i,*e);
	}
	ans[k]=tmp;
	for(int i=k-1;i>=0;--i)
	{
		++tmp;
		vis[dest[i]]=0;
		for(vit e=G[dest[i]].begin();e!=G[dest[i]].end();++e) if(!vis[*e])
			unite(dest[i],*e);
		ans[i]=tmp;
	}
	for(int i=0;i<=k;++i) printf("%d\n",ans[i]);
	return 0;
}
