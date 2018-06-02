#include<cstdio>
#include<algorithm>
const int MAXN=100000+5;
int n,b;
int a[MAXN];
int cnt[MAXN];
using std::lower_bound;
using std::upper_bound;
int main()
{
	scanf("%d%d",&n,&b);
	int t;
	for(int i=0;i<n;++i)
	{
		scanf("%d",a+i);
		if(a[i]==b) t=i;
	}
	for(int i=t-1;i>=0;--i)
	{
		cnt[i]=cnt[i+1];
		if(a[i]<b) --cnt[i];
		else ++cnt[i];
	}
	for(int i=t+1;i<n;++i)
	{
		cnt[i]=cnt[i-1];
		if(a[i]<b) --cnt[i];
		else ++cnt[i];
	}
	int ans=1;
	std::sort(cnt,cnt+t);
	std::sort(cnt+t+1,cnt+n);
	for(int i=0;i<t;++i)
		ans+=upper_bound(cnt+t+1,cnt+n,-cnt[i])-lower_bound(cnt+t+1,cnt+n,-cnt[i]);
	ans+=upper_bound(cnt+t+1,cnt+n,0)-lower_bound(cnt+t+1,cnt+n,0);
	ans+=upper_bound(cnt,cnt+t,0)-lower_bound(cnt,cnt+t,0);
	printf("%d\n",ans);
	return 0;
}
