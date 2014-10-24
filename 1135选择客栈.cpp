#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
const int MAXN=200000+10;
const int MAXK=50+10;
int n,k,p;
int pre[MAXN],num[MAXN][MAXK],col[MAXN],cost[MAXN];
int main()
{
	scanf("%d%d%d",&n,&k,&p);
	for(int i=1;i<=n;++i)
	{
		scanf("%d%d",col+i,cost+i);
		if(cost[i]<=p) pre[i]=i;
		else pre[i]=pre[i-1];
		for(int j=0;j<k;++j)
		{
			num[i][j]=num[i-1][j];
			if(j==col[i]) ++num[i][j];
		}
	}
	//for(int i=1;i<=n;++i) printf("%d ",num[i][0]);
	int ans=0;
	for(int i=2;i<=n;++i)
	{
		if(pre[i]==0) continue;
		int t=num[pre[i]][col[i]];
		if(cost[i]<=p) ans+=t-1;
		else ans+=t;
	}
	printf("%d\n",ans);
	return 0;
}
