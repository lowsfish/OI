#include<cstdio>
#include<algorithm>
const int MAXN=50000+5;
struct Node{
	int w,s;
	bool operator<(const Node& a)const
	{
		return w+s<a.w+a.s;
	}
}a[MAXN];
int pre[MAXN];
int n;
const int INF=~0U>>1;
int main()
{
	//freopen("1.in","r",stdin);
	scanf("%d",&n);
	for(int i=0;i<n;++i) scanf("%d%d",&a[i].w,&a[i].s);
	std::sort(a,a+n);
	pre[0]=0;
	for(int i=1;i<n;++i) pre[i]=pre[i-1]+a[i-1].w;
	int ans=-INF;
	for(int i=0;i<n;++i) ans=std::max(ans,pre[i]-a[i].s);
	printf("%d\n",ans);
	return 0;
}

