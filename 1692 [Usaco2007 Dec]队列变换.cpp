#include<cstdio>
#include<algorithm>
#define rep(i,n) for(int i=0;i<n;++i)
const int MAXN=30000+5;
const int MAXM=128;
int sa[MAXN<<1],rank[MAXN<<1],ta[MAXN<<1],tb[MAXN<<1];
char s[MAXN<<1],ans[MAXN];
inline bool cmp(int* y,int a,int b,int l)
{return y[a]==y[b] && y[a+l]==y[b+l];}
void Sort(int n,int m,int* x,int* y)
{
	static int c[MAXN<<1];
	rep(i,m) c[i]=0;
	rep(i,n) ++c[x[y[i]]];
	rep(i,m-1) c[i+1]+=c[i];
	for(int i=n-1;i>=0;--i) sa[--c[x[y[i]]]]=y[i];
}
void da(int n,int m)
{
	int j,p,i;
	int* x=ta,*y=tb;
	for(i=0;i<n;++i) x[i]=s[i],y[i]=i;
	Sort(n,m,x,y);
	for(j=1,p=1;p<n;m=p,j<<=1)
	{
		for(p=0,i=n-j;i<n;++i) y[p++]=i;
		for(i=0;i<n;++i) if(sa[i]>=j) y[p++]=sa[i]-j;
		Sort(n,m,x,y);
		for(std::swap(x,y),p=1,x[sa[0]]=0,i=1;i<n;++i)
			x[sa[i]]=cmp(y,sa[i],sa[i-1],j)?p-1:p++;
	}
}
int n,m;
int main()
{
	freopen("1.in","r",stdin);
	scanf("%d",&n);
	rep(i,n) getchar(),s[i]=getchar();
	rep(i,n) s[2*n-i]=s[i];
	s[n]=s[2*n+1]=0;
	da(2*n+2,MAXM);
	rep(i,2*n+2) rank[sa[i]]=i;
	int l=0,r=n-1,p=0;
	while(l<=r)
		ans[p++]=(rank[l]<rank[n*2-r]?s[l++]:s[r--]);
	rep(i,n)
	{
		if(i%80==0 && i) putchar(10);
		putchar(ans[i]);
	}
	putchar(10);
	return 0;
}
