#include<cstdio>
#include<algorithm>
const int MAXN=10000+5;
int n,_i,h,r;
int a[MAXN];
typedef std::pair<int,int> P;
P seg[MAXN];
#define x first
#define y second
int main()
{
	scanf("%d%d%d%d",&n,&_i,&h,&r);
	for(int i=0;i<r;++i)
	{
		int a,b;
		scanf("%d%d",&a,&b);
		if(a>b) std::swap(a,b);
		seg[i].x=a;seg[i].y=b;
	}
	std::sort(seg,seg+r);
	for(int i=0;i<r;++i)
	{
		if(i && seg[i].x==seg[i-1].x && seg[i].y==seg[i-1].y) continue;
		--a[seg[i].x+1];++a[seg[i].y];
	}
	int t=h;
	for(int i=1;i<=n;++i)
	{
		t+=a[i];
		printf("%d\n",t);
	}
	return 0;
}
