#include<cstdio>
#include<cstring>
#include<algorithm>
#define rep(i,n) for(int i=0;i<n;++i)
const int MAXN=100000+5;
char s1[MAXN<<1],s2[MAXN];
int s[MAXN<<1];
int sa[MAXN<<1],rank[MAXN<<1],height[MAXN<<1],ta[MAXN<<1],tb[MAXN<<1];
inline bool cmp(int* y,int a,int b,int l)
{
	return y[a]==y[b] && y[a+l]==y[b+l];
}
inline void Sort(int n,int m,int* x,int* y)
{
	static int c[MAXN<<1];
	rep(i,m) c[i]=0;
	rep(i,n) c[x[y[i]]]++;
	rep(i,m-1) c[i+1]+=c[i];
	for(int i=n-1;i>=0;--i) sa[--c[x[y[i]]]]=y[i];
}
inline void da(int n,int m)
{
	int* x=ta,*y=tb;
	int i,j,p;
	for(int i=0;i<n;++i) x[i]=s[i],y[i]=i;
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
inline void calheight(int n)
{
	int i,j,k=0;
	for(i=1;i<=n;++i) rank[sa[i]]=i;
	for(i=0;i<n;height[rank[i++]]=k)
		for(k?k--:0,j=sa[rank[i]-1];s[i+k]==s[j+k];++k);
}
int main()
{
//	freopen("1.in","r",stdin);
	scanf("%s%s",s1,s2);
	int n1=strlen(s1),n2=strlen(s2),n=n1+n2;
	s1[n1++]='a'+27;s1[n1]=0;
	++n;
	strcat(s1,s2);
	rep(i,n) s[i]=s1[i]-'a';
	s[n]=0;
	da(n+1,30);
	calheight(n);
	int ans=0;
	for(int i=1;i<n;++i) if((sa[i]<n1)^(sa[i-1]<n1)) ans=std::max(ans,height[i]);
	ans=std::min(ans,std::min(n1,n2));
	printf("%d\n",ans);
	return 0;
}
