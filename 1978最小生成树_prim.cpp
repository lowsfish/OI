#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<vector>
#define MAXSZ 105
using namespace std;
int cost[MAXSZ][MAXSZ];
int mincost[MAXSZ];
bool used[MAXSZ];
int V;
const int INF=(1<<29);
void init()
{
	for(int i=0;i<V;++i)
	{
		mincost[i]=INF;
		used[i]=0;
	}
}

int prim()
{
	int ans=0;
	init();
	mincost[0]=0;
	while(1)
	{
		int v=-1;
		for(int i=0;i<V;++i)
		{
			if(!used[i] && (v==-1 || mincost[i]<mincost[v]))
			{
				v=i;
			}
		}
		if(v==-1) break;
		ans+=mincost[v];
		used[v]=1;
		for(int i=0;i<V;++i)
		{
			mincost[i]=min(mincost[i],cost[v][i]);
		}
	}
	return ans;
}

int main()
{
	//freopen("1.in","r",stdin);
	cin>>V;
	for(int i=0;i<V;++i)
		for(int j=0;j<V;++j)
		{
			cin>>cost[i][j];
		}
	cout<<prim()<<endl;
	return 0;
}
