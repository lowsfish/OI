#include<cstdio>
#include<cstring>
#include<algorithm>
const int MAXN=50000+5;
const int MAXLOG=18;
int n,q;
int a[MAXN];
int mx[MAXN][MAXLOG],mn[MAXN][MAXLOG];
using std::max;
using std::min;
void RMQ_init()
{
	for(int i=0;i<n;++i) mx[i][0]=mn[i][0]=a[i];
	for(int i=1;(1<<i)<=n;++i)
		for(int j=0;n-j>=(1<<i);++j)
		{
			int k=j+(1<<i-1);
			mx[j][i]=max(mx[j][i-1],mx[k][i-1]);
			mn[j][i]=min(mn[j][i-1],mn[k][i-1]);
		}
}

int query(int a,int b)
{
	int k=0;
	while((1<<k+1)<=b-a+1) ++k;
	return max(mx[a][k],mx[b-(1<<k)+1][k])-min(mn[a][k],mn[b-(1<<k)+1][k]);
}
int main()
{
	scanf("%d%d",&n,&q);
	for(int i=0;i<n;++i) scanf("%d",a+i);
	RMQ_init();
	while(q--)
	{
		int a,b;
		scanf("%d%d",&a,&b);
		--a;--b;
		printf("%d\n",query(a,b));
	}
	return 0;
}
