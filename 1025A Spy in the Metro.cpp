#include<cstdio>
#include<algorithm>
#include<cstring>
const int MAXN=50+5;
const int MAXT=200+5;
const int INF=1<<28;
int n,T,M1,M2;
int t[MAXN];
int dp[MAXT][MAXN];
int has[MAXT][MAXN][2];
int src(int tim,int pla)
{
	if(dp[tim][pla]>0) return dp[tim][pla];
	if(tim==T)
	{
		if(pla==n) return 0;
		return INF;
	}
	int ans=src(tim+1,pla)+1;
	if(pla<n && has[tim][pla][0] && tim+t[pla]<=T)
		ans=std::min(ans,src(tim+t[pla],pla+1));
	if(pla>1 && has[tim][pla][1] && tim+t[pla-1]<=T)
		ans=std::min(ans,src(tim+t[pla-1],pla-1));
	return dp[tim][pla]=ans;
}
int main()
{
	//freopen("1.in","r",stdin);
	int kase=0;
	while(scanf("%d%d",&n,&T)==2 && n)
	{
		for(int i=1;i<n;++i) scanf("%d",t+i);
		memset(has,0,sizeof(has));
		scanf("%d",&M1);
		while(M1--)
		{
			int x,i=1;
			scanf("%d",&x);
			while(x<=T && i<=n)
			{
				has[x][i][0]=1;
				x+=t[i++];
			}
		}
		scanf("%d",&M2);
		while(M2--)
		{
			int x,i=n;
			scanf("%d",&x);
			while(x<=T && i>0)
			{
				has[x][i][1]=1;
				x+=t[--i];
			}
		}
		memset(dp,0,sizeof(dp));
		int ans=src(0,1);
		printf("Case Number %d: ",++kase);
		if(ans>=INF) printf("impossible\n");
		else printf("%d\n",ans);
	}
	return 0;
}
