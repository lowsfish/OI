#include<cstdio>
#include<algorithm>
const int MAXN=100000+10;
const int MAXM=1000000+10;
int s[MAXM],a[MAXN],cnt[MAXM],;
int main()
{
	int n,mx=0;
	scanf("%d",&n);
	for(int i=0;i<n;++i)
		scanf("%d",a+i),cnt[a[i]]++,mx=std::max(mx,a[i]);
	for(int i=1;i<=mx;++i) if(cnt[i])
	{
		for(int j=i;j<=mx;j+=i) s[j]+=cnt[i];
	}
	for(int i=0;i<n;++i) printf("%d\n",s[a[i]]-1);
	return 0;
}
