#include<stdio.h>
#include<string.h>
const int MAXN=100000+5;
int head[MAXN],to[MAXN<<1],next[MAXN<<1],c[MAXN<<1];
int t1[MAXN],t2[MAXN];
inline void addEdge(int u,int v)
{
	static int cnt=0;
	to[cnt]=v;
	next[cnt]=head[u];
	head[u]=cnt;
	c[cnt++]=1;
}
int len=0,pos;
int dfs(int u,int fa)
{
	int mx1=0,mx2=0;
	for(int i=head[u];~i;i=next[i]) if(to[i]!=fa)
	{
		int t=dfs(to[i],u)+c[i];
		if(t>mx1) mx2=mx1,mx1=t,t2[u]=t1[u],t1[u]=i;
		else if(t>mx2) mx2=t,t2[u]=i;
	}
	if(mx1+mx2>len) len=mx1+mx2,pos=u;
	return mx1;
}
int tot;
int n,k;
void input()
{
	memset(head,-1,sizeof head);
	scanf("%d%d",&n,&k);
	tot=(n-1)<<1;
	for(int i=1;i<n;++i)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		addEdge(u,v);
		addEdge(v,u);
	}
}
int main()
{
	input();
	dfs(1,0);
	tot-=len-1;
	if(k==2)
	{
		len=0;
		for(int i=t1[pos];i;i=t1[to[i]]) c[i]=c[i^1]=-1;
		for(int i=t2[pos];i;i=t1[to[i]]) c[i]=c[i^1]=-1;
		dfs(1,0);
		tot-=len-1;
	}
	printf("%d\n",tot);
	return 0;
}
