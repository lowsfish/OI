#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
#define p_b push_back
const int MAXN=5000+5;
std::vector<int> G[MAXN];
typedef std::vector<int>::iterator vit;
int n;
int fa[MAXN],dep[MAXN],temp[MAXN];
int mx;
void dfs(int u)
{
	temp[dep[u]]++;
	mx=std::max(mx,temp[dep[u]]);
	for(vit e=G[u].begin();e!=G[u].end();++e) if(*e!=fa[u])
	{
		fa[*e]=u;
		dep[*e]=dep[u]+1;
		dfs(*e);
	}
}
typedef long long LL;
LL t1[MAXN],t2[MAXN],ans;
int main()
{
//	freopen("1.in","r",stdin);
	scanf("%d",&n);
	for(int i=0;i<n-1;++i)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		G[u].p_b(v);
		G[v].p_b(u);
	}
	for(int i=1;i<=n;++i)
	{
		memset(t1,0,sizeof(t1));
		memset(t2,0,sizeof(t2));
		for(vit e=G[i].begin();e!=G[i].end();++e)
		{
			fa[*e]=i;dep[*e]=1;
			dfs(*e);
			for(int j=1;j<=mx;++j)
			{
				ans+=t2[j]*temp[j];
				t2[j]+=temp[j]*t1[j];
				t1[j]+=temp[j];
			}
			for(int j=1;j<=mx;++j) temp[j]=0;
		}
	}
	printf("%lld\n",ans);
}
