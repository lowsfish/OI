#include<cstdio>
#include<algorithm>
const int MAXN=100+5;
const int INF=1<<28;
const int MAXS=10000+5;
int a[MAXN];
int dpmin[MAXS],dpmax[MAXS];
int n,s;
int srcmin(int sum)
{
	if(sum==0) return 0;
	if(dpmin[sum]>0) return dpmin[sum];
	int ans=INF;
	for(int i=0;i<n;++i) if(sum>=a[i])
		ans=std::min(ans,srcmin(sum-a[i])+1);
	return dpmin[sum]=ans;
}
int srcmax(int sum)
{
	if(sum==0) return 0;
	if(dpmax[sum]!=0) return dpmax[sum];
	int ans=-INF;
	for(int i=0;i<n;++i) if(sum>=a[i])
		ans=std::max(ans,srcmax(sum-a[i])+1);
	return dpmax[sum]=ans;
}
int main()
{
	freopen("1.in","r",stdin);
	scanf("%d%d",&n,&s);
	for(int i=0;i<n;++i) scanf("%d",a+i);
	printf("%d\n%d\n",srcmin(s),srcmax(s));
	return 0;
}
