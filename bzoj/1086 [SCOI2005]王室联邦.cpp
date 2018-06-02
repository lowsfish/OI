#include<cstdio>
#include<cstring>
#include<vector>
#define foreach(e,x) for(__typeof(x.begin()) e=x.begin();e!=x.end();++e)
const int MAXN=1000+5;
int n,b;
using std::vector;
vector<int> G[MAXN];
typedef vector<int>::iterator vit;
int own[MAXN];
int id[MAXN];
int tot=0;
vector<int> dfs(int u,int fa)
{
	vector<int> ans;
	foreach(e,G[u]) if(*e!=fa)
	{
		vector<int> t=dfs(*e,u);
		ans.insert(ans.end(),t.begin(),t.end());
		if(ans.size()>=b)
		{
			id[++tot]=u;
			foreach(i,ans) own[*i]=tot;
			ans.clear();
		}
	}
	ans.push_back(u);
	return ans;
}
int main()
{
	scanf("%d%d",&n,&b);
	if(b>n)
	{
		printf("0\n");
		return 0;
	}
	for(int i=0;i<n-1;++i)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		G[u].push_back(v);
		G[v].push_back(u);
	}
	vector<int> ans=dfs(1,0);
	foreach(e,ans) own[*e]=tot;
	printf("%d\n",tot);
	for(int i=1;i<=n;++i)
		printf("%d%c",own[i],i==n?'\n':' ');
	for(int i=1;i<=tot;++i)
		printf("%d%c",id[i],i==tot?'\n':' ');
	return 0;
}
