#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=100+10;
int n;
int a[MAXN];
int main()
{
	//freopen("1.in","r",stdin);
	scanf("%d",&n);
	for(int i=0;i<n;++i) scanf("%d",a+i);
	sort(a,a+n);
	int ans=1;
	for(int i=0;i<n;++i)
		for(int j=i+1;j<n;++j)
		{
			int sum=2;
			int d=a[j]-a[i],t=a[j];
			for(int k=j+1;k<n;++k) if(a[k]-t==d)
			{
				++sum;
				t=a[k];
			}
			ans=max(ans,sum);
		}
	printf("%d\n",ans);
	return 0;
}
