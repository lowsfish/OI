#include<cstdio>
const int MAXN=500000+5;
int dp[MAXN];
int deq[MAXN],qh,qt;
int sum[MAXN];
int n,m;
inline int sqr(int x)
{
	return x*x;
}
inline int getDp(int i,int j)
{
	return dp[j]+m+sqr(sum[i]-sum[j]);
}
inline int getUp(int j,int k)
{
	return dp[j]+sqr(sum[j])-(dp[k]+sqr(sum[k]));
}
inline int getDown(int j,int k)
{
	return 2*(sum[j]-sum[k]);
}
int main()
{
	while(scanf("%d%d",&n,&m)!=EOF)
	{
		for(int i=1;i<=n;++i) scanf("%d",sum+i);
		for(int i=1;i<=n;++i) sum[i]+=sum[i-1];
		qh=0,qt=1;
		for(int i=1;i<=n;++i)
		{
			while(qh+1<qt && getUp(deq[qh+1],deq[qh])<=sum[i]*getDown(deq[qh+1],deq[qh])) qh++;
			dp[i]=getDp(i,deq[qh]);
			while(qh+1<qt && getUp(i,deq[qt-1])*getDown(deq[qt-1],deq[qt-2])<=getUp(deq[qt-1],deq[qt-2])*getDown(i,deq[qt-1])) --qt;
			deq[qt++]=i;
		}
		printf("%d\n",dp[n]);
	}
	return 0;
}
