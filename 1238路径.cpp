#include<iostream>
#include<cstdio>
#include<vector>
#include<cstring>
#include<queue>
using namespace std;

const int MAXV=1000+5;
int mat[MAXV][MAXV];
bool vis[MAXV];
int V,E;
const int INF=(1<<29)-1;
int minlen=INF,mincost=INF;

void input_init()
{
	memset(vis,0,sizeof(vis));
	scanf("%d%d",&V,&E);
	for(int i=0;i<=V;++i)
		for(int j=0;j<=V;++j)
		{
			mat[i][j]=i==j?0:INF;
		}
	for(int i=0;i<E;++i)
	{
		int from,to,cost;
		scanf("%d%d%d",&from,&to,&cost);
		mat[from][to]=min(mat[from][to],cost);
	}
}

void dfs(int v,int nowlen,int nowcost)
{
	if(nowlen>minlen) return;
	if(v==1 &&(nowlen<minlen || (nowlen==minlen && nowcost<mincost)))
	{
		minlen=nowlen;
		mincost=nowcost;
		return;
	}
	for(int i=0;i<V;++i)
	{
		if(mat[v][i]!=INF && !vis[i]) {
			vis[i]=1;
			dfs(i,nowlen+1,nowcost+mat[v][i]);
			vis[i]=0;
		}
	}
}
int main()
{
	//freopen("1.in","r",stdin);
	input_init();
	dfs(0,0,0);
	printf("%d\n",mincost);
	return 0;
}
