#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=10;
int mat[MAXN][MAXN],n,color[MAXN];
int tot;
void dfs(int cur,int clr)
{
		for(int i=0;i<cur;++i) if(mat[i][cur] && color[i]==clr) return;
		if(cur==n-1) 
		{
			++tot;
			return;
		}
		for(int i=1;i<=4;++i)
		{
			color[cur+1]=i;
			dfs(cur+1,i);
		}
}

int main()
{
	freopen("1.in","r",stdin);
	scanf("%d",&n);
	for(int i=0;i<n;++i)
		for(int j=0;j<n;++j)
		{
			scanf("%d",&mat[i][j]);
		}
	for(int i=1;i<=4;++i)
	{
		color[0]=i;
		dfs(0,i);
	}

	printf("%d\n",tot);
	return 0;
}
