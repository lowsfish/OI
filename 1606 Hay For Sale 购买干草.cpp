#include<cstdio>
#include<algorithm>
const int MAXN=50000+10;
int dp[MAXN];
int c,h;
void ZeroOne(int w,int v)
{
	for(int i=c;i>=w;--i)
		dp[i]=std::max(dp[i],dp[i-w]+v);
}
int w[MAXN];
int main()
{
	scanf("%d%d",&c,&h);
	for(int i=0;i<h;++i) scanf("%d",w+i);
	for(int i=0;i<h;++i)
		ZeroOne(w[i],w[i]);
	printf("%d\n",dp[c]);
	return 0;
}
