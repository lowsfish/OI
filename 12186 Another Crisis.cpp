#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
const int MAXN=100000+5;
const int INF=1<<28;
std::vector<int> son[MAXN];
int T,n;
void init()
{
	for(int i=0;i<=n;++i) son[i].clear();
}
int src(int u)
{
	if(son[u].empty()) return 1;
	int k=son[u].size();
	std::vector<int> d;
	for(int i=0;i<k;++i)
		d.push_back(src(son[u][i]));
	std::sort(d.begin(),d.end());
	int c=(k*T-1)/100+1;
	int ans=0;
	for(int i=0;i<c;++i) ans+=d[i];
	return ans;
}

int main()
{
	//freopen("1.in","r",stdin);
	while(scanf("%d%d",&n,&T)!=EOF && n)
	{
		init();
		for(int i=1;i<=n;++i)
		{
			int t;
			scanf("%d",&t);
			son[t].push_back(i);
		}
		printf("%d\n",src(0));
	}
	return 0;
}
