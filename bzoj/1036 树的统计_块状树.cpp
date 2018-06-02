#include<cstdio>
#include<cmath>
#include<vector>
#include<algorithm>
#define pb push_back
const int INF=~0U>>1;
const int MAXN=30000+10;
std::vector<int> G[MAXN],Gt[MAXN];
typedef std::vector<int>::iterator it;
int n,q,w[MAXN],lim,dep[MAXN],fa[MAXN];
int own[MAXN],Max[MAXN],Sum[MAXN];
void build(int u,int f,int d)
{
	fa[u]=f;dep[u]=d;
	int tmp=own[u];
	for(it e=G[u].begin();e!=G[u].end();++e)
		if(*e!=f)
		{
			if(Sum[tmp]++<lim)
				Gt[u].pb(*e),own[*e]=tmp;
			build(*e,u,d+1);
		}
}
void dfs(int u,int s,int m)
{
	Sum[u]=s+=w[u];m=Max[u]=std::max(m,w[u]);
	for(it e=Gt[u].begin();e!=Gt[u].end();++e)
		dfs(*e,s,m);
}
void change(int u,int t)
{
	w[u]=t;
	if(own[u]==u) dfs(u,0,-INF);
	else dfs(u,Sum[fa[u]],Max[fa[u]]);
}
int asksum(int u,int v)
{
	int s=0;
	while(u!=v)
	{
		if(dep[u]<dep[v]) std::swap(u,v);
		if(own[u]==own[v])
			s+=w[u],u=fa[u];
		else
		{
			if(dep[own[u]]<dep[own[v]]) std::swap(u,v);
			s+=Sum[u];u=fa[own[u]];
		}
	}
	return s+w[u];
}
int askmax(int u,int v)
{
	int ans=-INF;
	while(u!=v)
	{
		if(dep[u]<dep[v]) std::swap(u,v);
		if(own[u]==own[v])
			ans=std::max(ans,w[u]),u=fa[u];
		else
		{
			if(dep[own[u]]<dep[own[v]]) std::swap(u,v);
			ans=std::max(ans,Max[u]);u=fa[own[u]];
		}
	}
	return std::max(ans,w[u]);
}
int nextint()
{
	char c=getchar();
	while(c!='-' && (c<'0' || c>'9')) c=getchar();
	int n=0,s=1;
	if(c=='-') s=-1,c=getchar();
	while(c>='0' && c<='9') n=n*10+c-'0',c=getchar();
	return n*s;
}
int main()
{
	freopen("1.in","r",stdin);
	freopen("1.out","w",stdout);
	n=nextint();
	for(int i=1;i<n;++i)
	{
		int u,v;
		u=nextint();v=nextint();
		G[u].pb(v);G[v].pb(u);
	}
	for(int i=1;i<=n;++i) w[i]=nextint(),own[i]=i;
	build(1,-1,0);
	for(int i=1;i<=n;++i) if(own[i]==i) dfs(i,0,-INF);
	q=nextint();
	char s[10];
	while(q--)
	{
		int a,b;
		scanf("%s",s);
		a=nextint();b=nextint();
		if(s[0]=='C') change(a,b);
		else if(s[1]=='S') printf("%d\n",asksum(a,b));
		else printf("%d\n",askmax(a,b));
	}
	return 0;
}
