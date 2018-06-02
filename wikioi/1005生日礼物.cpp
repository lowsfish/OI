#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
const int MAXN=8+3;
const int MAXM=10+5;
int a[MAXN][MAXM],b[MAXN];
int res[MAXM]={0};
int n,m;
const int INF=(1<<29)-1;
int ans=INF;
void input()
{
	scanf("%d%d",&n,&m);
	for(int i=0;i<n;++i)
		for(int j=0;j<m;++j)
		{
			scanf("%d",&a[i][j]);
		}
	for(int i=0;i<n;++i) scanf("%d",b+i);
}

bool judge()
{
	if(res[0]==0) return 0;
	for(int i=0;i<m-1;++i) if(res[i]!=res[i+1]) return 0;
	return 1;
}

void dfs(int nn)
{
	if(judge()) ans=min(ans,m*res[0]);
	if(nn>=n) return;
	for(int i=0;i<=b[nn];++i)
	{
		bool ok=1;
		for(int j=0;j<m;++j) {
			res[j]+=i*a[nn][j];
			if(res[j]*m>ans) ok=0;	//如果其中任意一个超了，就不用往下搜索了
		}
		if(ok)
			dfs(nn+1);
		for(int j=0;j<m;++j) res[j]-=i*a[nn][j];
	}
}

int main()
{
	//freopen("1.in","r",stdin);
	input();
	dfs(0);
	if(ans>=1000) printf("alternative!\n");
	else printf("%d\n",ans);
	return 0;
}
