#include<cstdio>
#include<algorithm>
const int MAXN=30000+10;
const int INF=~0U>>1;
int n;
int g[MAXN],d[MAXN];
int LIS(int* a)
{
	int ans=0;
	for(int i=1;i<=n;++i) g[i]=INF;
	for(int i=0;i<n;++i)
	{
		int k=std::upper_bound(g+1,g+1+n,a[i])-g;
		d[i]=k;
		ans=std::max(ans,k);
		g[k]=a[i];
	}
	return ans;
}
int a[MAXN<<1];
int main()
{
	scanf("%d",&n);
	for(int i=0;i<n;++i) scanf("%d",a+i),a[2*n-i-1]=a[i];
	printf("%d\n",n-std::max(LIS(a),LIS(a+n)));
	return 0;
}
