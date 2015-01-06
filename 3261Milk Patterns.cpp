#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=20000+10;
const int MAXM=1000000+5;
inline bool cmp(int *r,int a,int b,int l)
{
	return r[a]==r[b] && r[a+l] == r[b+l];
}
int s[MAXN],sa[MAXN],t[MAXN],t2[MAXN];
void Sort(int n,int m,int *x,int *y)
{
	static int c[MAXM];
	int i;
	for(i=0;i<m;++i) c[i]=0;
	for(i=0;i<n;++i) c[x[y[i]]]++;
	for(i=1;i<m;++i) c[i]+=c[i-1];
	for(i=n-1;i>=0;--i) sa[--c[x[y[i]]]]=y[i];
}
void da(int n,int m)
{
	int i,j,p,*x=t,*y=t2;
	for(i=0;i<n;++i) y[i]=i,x[i]=s[i];
	Sort(n,m,x,y);
	for(j=1,p=1;p<n;m=p,j<<=1)
	{
		for(p=0,i=n-j;i<n;++i) y[p++]=i;
		for(i=0;i<n;++i) if(sa[i]>=j) y[p++]=sa[i]-j;
		Sort(n,m,x,y);
		for(swap(x,y),p=1,x[sa[0]]=0,i=1;i<n;++i)
			x[sa[i]]=cmp(y,sa[i-1],sa[i],j)?p-1:p++;
	}
}
int rank[MAXN],height[MAXN];
void calheight(int n)
{
	int i,j,k=0;
	for(i=1;i<=n;++i) rank[sa[i]]=i;
	for(i=0;i<n;height[rank[i++]]=k)
		for(k?k--:0,j=sa[rank[i-1]];s[i+k]==s[j+k];++k);
}
int n,k;
int work(int M)
{
	int cnt=0;
	for(int i=1;i<=n;++i)
	{
		if(height[i]<M) cnt=0;
		else
		{
			++cnt;
			if(cnt>=k) return 1;
		}
	}
	return 0;
}
int main()
{
	freopen("1.in","r",stdin);
	scanf("%d%d",&n,&k);
	for(int i=0;i<n;++i) scanf("%d",s+i);
	da(n+1,MAXM);
	calheight(n);
	int L=1,R=n;
	while(L<=R)
	{
		int M=(L+R)>>1;
		if(work(M)) L=M+1;
		else R=M-1;
	}
	printf("%d\n",R);
	return 0;
}
