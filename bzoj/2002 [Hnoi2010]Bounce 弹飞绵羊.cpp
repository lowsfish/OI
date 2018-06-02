#include<cstdio>
#include<cmath>
const int MAXN=200000+5;
int next[MAXN],reach[MAXN],len[MAXN],s,n,m;
void remark(int t)
{
	int l=t*s,r=l+s-1;if(r>=n) r=n-1;
	for(int i=r;i>=l;--i)
	{
		len[i]=1;
		int& rch=reach[i];rch=next[i];
		if(rch<=r) len[i]+=len[rch],rch=reach[rch];
	}
}
int query(int st)
{
	int ans=0;
	while(st<n) ans+=len[st],st=reach[st];
	return ans;
}
void change(int p,int nxt)
{
	next[p]=nxt;
	remark(p/s);
}
int main()
{
	scanf("%d",&n);
	int t;
	for(int i=0;i<n;++i) scanf("%d",&t),next[i]=i+t;
	s=sqrt(n)+1;
	for(int i=0;i<s;++i) remark(i);
	scanf("%d",&m);
	while(m--)
	{
		int k,a,b;
		scanf("%d%d",&k,&a);
		if(k==1) printf("%d\n",query(a));
		else scanf("%d",&b),change(a,b+a);
	}
	return 0;
}
