#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=(100000+5)<<1;
char s[MAXN];
int sa[MAXN],t[MAXN],t2[MAXN],*x=t,*y=t2,n,m;
inline bool cmp(int a,int b,int l)
{
	return y[a]==y[b] && y[a+l]==y[b+l];
}
void Sort()
{
	int i;
	static int c[MAXN];
	for(i=0;i<m;++i) c[i]=0;
	for(i=0;i<n;++i) c[x[y[i]]]++;
	for(i=1;i<m;++i) c[i]+=c[i-1];
	for(i=n-1;i>=0;--i) sa[--c[x[y[i]]]]=y[i];
}
void da()
{
	int i,j,p;
	for(i=0;i<n;++i) y[i]=i,x[i]=s[i];
	Sort();
	for(p=1,j=1;p<n;m=p,j<<=1)
	{
		for(p=0,i=n-j;i<n;++i) y[p++]=i;
		for(i=0;i<n;++i) if(sa[i]>=j) y[p++]=sa[i]-j;
		Sort();
		for(swap(x,y),p=1,x[sa[0]]=0,i=1;i<n;++i)
			x[sa[i]]=cmp(sa[i-1],sa[i],j)?p-1:p++;
	}
}

int main()
{
	cin.getline(s,MAXN);
	n=strlen(s);
	m=256;
	for(int i=0;i<n;++i) s[n+i]=s[i];
	n<<=1;
	s[n++]=0;
	da();
	int S=n>>1;
	for(int i=1;i<n;++i) if(sa[i]<S) putchar(s[S+sa[i]-1]);
	putchar(10);
	return 0;
}
