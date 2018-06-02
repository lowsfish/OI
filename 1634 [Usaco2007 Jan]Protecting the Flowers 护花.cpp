#include<cstdio>
#include<cstring>
#include<algorithm>
typedef long long LL;
const int MAXN=100000+5;
struct Cow{
	int t,d;
	double s;
	Cow() {}
	Cow(int t,int d):t(t),d(d) {s=(double)t/d;}
	bool operator<(const Cow& c)const
	{
		return s<c.s;
	}
}a[MAXN];
int n;
int main()
{
	//freopen("1.in","r",stdin);
	scanf("%d",&n);
	for(int i=0;i<n;++i)
	{
		int t,d;
		scanf("%d %d",&t,&d);
		a[i]=Cow(t,d);
	}
	std::sort(a,a+n);
	LL ans=0;
	int sum=0;
	for(int i=0;i<n;++i) sum+=a[i].d;
	for(int i=0;i<n;++i)
	{
		sum-=a[i].d;
		ans+=2*sum*a[i].t;
	}
	printf("%lld\n",ans);
	return 0;
}

