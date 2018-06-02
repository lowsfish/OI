#include<cstdio>
#include<algorithm>
#define fr first
#define sc second
const int MAXN=1000000+10;
int deq[MAXN];
int qh,qt;
int n;
int a[MAXN],b[MAXN];
int main()
{
	scanf("%d",&n);
	int ans=0;
	for(int i=0;i<n;++i)
	{
		scanf("%d%d",a+i,b+i);
		while(qh<qt && a[deq[qh]]>b[i]) ++qh;
		if(qh<qt) ans=std::max(ans,i-deq[qh]+1);
		int t=i;
		while(qh<qt && a[i]>a[deq[qt-1]]) t=deq[--qt];
		a[t]=a[i];deq[qt++]=t;
	}
	printf("%d\n",ans);
	return 0;
}
