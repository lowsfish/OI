#include<cstdio>
#include<algorithm>
typedef long long LL;
const int MAXN=50000+5;
LL dp[MAXN];
LL sum[MAXN];
int deq[MAXN],qh,qt;
int n,l;
inline LL sqr(LL x)
{
	return x*x;
}
inline LL getDp(int i,int j)
{
	return dp[j]+sqr(sum[i]-sum[j]+i-j-1-l);
}
inline LL getUp(int j,int k)
{
	return dp[j]+sqr(sum[j]+j)-(dp[k]+sqr(sum[k]+k));
}
inline LL getDown(int j,int k)
{
	return sum[j]+j-(sum[k]+k);
}
inline LL getRight(int i)
{
	return (sum[i]+i-l-1)<<1;
}
int main()
{
	freopen("1.in","r",stdin);
	scanf("%d%d",&n,&l);
	for(int i=1;i<=n;++i) scanf("%lld",sum+i);
	for(int i=1;i<=n;++i) sum[i]+=sum[i-1];
	qh=0,qt=1;
	for(int i=1;i<=n;++i)
	{
		while(qh+1<qt && getUp(deq[qh+1],deq[qh])<getRight(i)*getDown(deq[qh+1],deq[qh])) ++qh;
		dp[i]=getDp(i,deq[qh]);
		while(qh+1<qt && getUp(i,deq[qt-1])*getDown(deq[qt-1],deq[qt-2]) < getUp(deq[qt-1],deq[qt-2])*getDown(i,deq[qt-1])) --qt;
		deq[qt++]=i;
	}
	printf("%lld\n",dp[n]);
	return 0;
}
