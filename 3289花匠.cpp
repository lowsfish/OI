#include<iostream>
#include<cstdio>
using namespace std;
const int MAXN=1e5+10;
int a[MAXN];
int n;
int main()
{
	freopen("1.in","r",stdin);
	scanf("%d",&n);
	for(int i=0;i<n;++i)
	{
		scanf("%d",a+i);
	}
	int ans=0,t=a[0],st=0;
	for(int i=1;i<n;++i)
	{
		if(a[i]>a[i-1] && st!=1) {++ans;st=1;}
		if(a[i]<a[i-1] && st!=-1) {++ans;st=-1;}
	}
	printf("%d\n",ans+1);
	return 0;
}
