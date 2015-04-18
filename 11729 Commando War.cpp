#include<cstdio>
#include<algorithm>
const int MAXN=1000+5;
struct Node{
	int b,j;
	bool operator<(const Node& a)const
	{
		return j>a.j;
	}
}a[MAXN];
int n,t[MAXN];
int main()
{
	int kase=0;
	while(scanf("%d",&n)!=EOF && n)
	{
		for(int i=0;i<n;++i) scanf("%d%d",&a[i].b,&a[i].j);
		std::sort(a,a+n);
		t[0]=a[0].b;
		for(int i=1;i<n;++i) t[i]=t[i-1]+a[i].b;
		int ans=0;
		for(int i=0;i<n;++i) ans=std::max(ans,t[i]+a[i].j);
		printf("Case %d: %d\n",++kase,ans);
	}
	return 0;
}
