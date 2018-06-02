#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=20000+10;
int s[MAXN],t[MAXN],t2[MAXN],sa[MAXN];
int *x=t,*y=t2;
inline bool cmp(int a,int b,int l)
{
	return y[a]==y[b] && y[a+l]==y[b+l];
}
void Sort(int n,int m)
{
	int i;
	static int c[MAXN];
	for(i=0;i<m;++i) c[i]=0;
	for(i=0;i<n;++i) c[x[y[i]]]++;
	for(i=1;i<m;++i) c[i]+=c[i-1];
	for(i=n-1;i>=0;--i) sa[--c[x[y[i]]]]=y[i];
}

void da(int n,int m)
{
	int i,j,p;
	for(i=0;i<n;++i) y[i]=i,x[i]=s[i];
	Sort(n,m);
	for(p=1,j=1;p<n;m=p,j<<=1)
	{
		for(p=0,i=n-j;i<n;++i) y[p++]=i;
		for(i=0;i<n;++i) if(sa[i]>=j) y[p++]=sa[i]-j;
		Sort(n,m);
		for(swap(x,y),p=1,x[sa[0]]=0,i=1;i<n;++i)
			x[sa[i]]=cmp(sa[i-1],sa[i],j)?p-1:p++;
	}
}
int rank[MAXN],height[MAXN];
void calheight(int n)
{
	int i,j,k=0;
	for(i=1;i<=n;++i) rank[sa[i]]=i;
	for(i=0;i<n;height[rank[i++]]=k)
		for(k?k--:0,j=sa[rank[i]-1];s[i+k]==s[j+k];++k);
	/*for(i=0;i<n;++i)
	{
		if(k) --k;
		j=sa[rank[i]-1];
		while(s[i+k] == s[j+k]) ++k;
		height[rank[i]]=k;
	}*/
}
const int INF=1<<27;
bool work(int n,int k)
{
	int mx,mn;
	mx=mn=sa[1];
	for(int i=2;i<=n;++i)
	{
		if(height[i]<k) mx=mn=sa[i];
		else
		{
			mx=max(mx,sa[i]);
			mn=min(mn,sa[i]);
			if(mx-mn>k) return 1;
		}
	}
	return 0;
}

int main()
{
	int n;
	while(scanf("%d",&n)!=EOF && n)
	{
		int j;
		scanf("%d",&j);--n;
		for(int i=0;i<n;++i)
		{
			int k;
			scanf("%d",&k);
			s[i]=k-j+100;
			j=k;
		}
		s[n]=0;
		da(n+1,200);
		calheight(n);
		int L=1,R=n>>1;
		while(L<=R)	
		{
			int M=(L+R)>>1;
			if(work(n,M)) L=M+1;
			else R=M-1;
		}
		if(R>=4) printf("%d\n",R+1);
		else printf("0\n");
	}
	return 0;
}
