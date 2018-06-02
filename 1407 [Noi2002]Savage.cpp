#include<cstdio>
#include<algorithm>
typedef long long LL;
#define int LL
const int MAXN=15+5;
const int MAXM=1000000;
int extgcd(int a,int b,int& x,int& y)
{
	int d=a;
	if(b)
	{
		d=extgcd(b,a%b,y,x);
		y-=(a/b)*x;
	}
	else x=1,y=0;
	return d;
}
int calc(int a,int b,int c)
{
	int x,y,d=extgcd(a,c,x,y);
	if(b%d) return -1;
	x*=b/d;
	while(x>c/d) x-=c/d;
	while(x<0) x+=c/d;
	return x;
}
int n;
int c[MAXN],p[MAXN],l[MAXN];
int judge(int m)
{
	for(int i=0;i<n;++i)
		for(int j=i+1;j<n;++j)
		{
			LL d;
			if(p[i]>p[j]) d=calc(p[i]-p[j],c[j]-c[i],m);
			else d=calc(p[j]-p[i],c[i]-c[j],m);
			if(d!=-1 && d<=std::min(l[i],l[j])) return 0;
		}
	return 1;
}
#undef int
int main()
{
	scanf("%lld",&n);
	for(int i=0;i<n;++i) scanf("%lld%lld%lld",c+i,p+i,l+i);
	int ans=*std::max_element(c,c+n);
	for(;!judge(ans);++ans);
	printf("%d\n",ans);
	return 0;
}
