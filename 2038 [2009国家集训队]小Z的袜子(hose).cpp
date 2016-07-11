#include<cstdio>
#include<algorithm>
#include<cmath>
const int MAXN=50000+5;
typedef long long LL;
LL gcd(LL a,LL b)
{
	return b==0?a:gcd(b,a%b);
}
int n,m,sz;
int a[MAXN];
struct Ask{
	int l,r,id;
	bool operator<(const Ask& rhs) const
	{
		if(l/sz == rhs.l/sz) return r<rhs.r;
		return l/sz<rhs.l/sz;
	}
}ask[MAXN];
LL ansa[MAXN],ansb[MAXN];
LL num[MAXN];
LL sum=0;
inline void modify(int x,int f)
{
	sum-=(LL)num[x]*(num[x]-1);
	num[x]+=f;
	sum+=(LL)num[x]*(num[x]-1);
}
int main()
{
	//freopen("1.in","r",stdin);
	scanf("%d%d",&n,&m);
	sz=sqrt(n)+1;
	for(int i=1;i<=n;++i) scanf("%d",a+i);
	for(int i=0;i<m;++i) scanf("%d%d",&ask[i].l,&ask[i].r),ask[i].id=i;
	std::sort(ask,ask+m);
	int l=1,r=0;
	for(int i=0;i<m;++i)
	{
		while(l<ask[i].l) modify(a[l++],-1);
		while(r>ask[i].r) modify(a[r--],-1);
		while(l>ask[i].l) modify(a[--l],1);
		while(r<ask[i].r) modify(a[++r],1);
		LL& t1=ansa[ask[i].id],&t2=ansb[ask[i].id];
		if(l==r)
		{
			t1=0;t2=1;
			continue;
		}
		t1=sum;t2=(LL)(r-l+1)*(r-l);
		LL k=gcd(t1,t2);
		t1/=k;t2/=k;
	}
	for(int i=0;i<m;++i) printf("%lld/%lld\n",ansa[i],ansb[i]);
	return 0;
}

