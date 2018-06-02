#include<cstdio>
#include<algorithm>
const int MAXN=100000+5;
typedef long long LL;
int n;
int h[MAXN];
int L[MAXN],R[MAXN];
int st[MAXN];
void work()
{
	int t=0;
	for(int i=0;i<n;++i)
	{
		while(t && h[st[t-1]]>=h[i]) --t;
		L[i]=t==0?t:(st[t-1]+1);
		st[t++]=i;
	}
	t=0;
	for(int i=n-1;i>=0;--i)
	{
		while(t && h[st[t-1]]>=h[i]) --t;
		R[i]=t==0?n:st[t-1];
		st[t++]=i;
	}
	LL ans=0;
	for(int i=0;i<n;++i)
		ans=std::max(ans,(LL)h[i]*(R[i]-L[i]));
	printf("%lld\n",ans);
}
int main()
{
//	freopen("1.in","r",stdin);
	while(scanf("%d",&n)!=EOF && n)
	{
		for(int i=0;i<n;++i) scanf("%d",h+i);
		work();
	}
	return 0;
}
