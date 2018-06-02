#include<cstdio>
#include<iostream>
#include<algorithm>
typedef long long LL;
const LL MAXN=100+5;
const LL INF=(LL)1<<60;
int n;
int l[MAXN];
LL dp[MAXN][MAXN];
LL src(LL x,LL y)
{
	if(dp[x][y]>0) return dp[x][y];
	if(y==x) return 0;
	if(y-x==1) return l[x]*l[y]*l[y+1];
	LL ans=INF;
	for(LL i=x;i<y;++i)
		ans=std::min(ans,src(x,i)+src(i+1,y)+l[x]*l[i+1]*l[y+1]);
	return dp[x][y]=ans;
}

int main()
{
	freopen("1.in","r",stdin);
	scanf("%d",&n);
	for(LL i=0;i<=n;++i) scanf("%d",l+i);
	std::cout<<src(0,n-1)<<std::endl;
	return 0;
}
