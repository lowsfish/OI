#include<cstdio>
#include<algorithm>
#include<cstring>
const int MAXN=50000+5;
int f[MAXN<<1],sum[MAXN];
typedef std::pair<int,int> P;
#define x first
#define kd second
P cow[MAXN];
int n;
int main()
{
	//freopen("1.in","r",stdin);
	scanf("%d",&n);
	for(int i=0;i<n;++i)
	{
		scanf("%d%d",&cow[i].kd,&cow[i].x);
		if(!cow[i].kd) cow[i].kd=-1;
	}
	std::sort(cow,cow+n);
	int ans=0;
	memset(f,-1,sizeof f);
	for(int i=0;i<n;++i) sum[i]=sum[i-1]+cow[i].kd;
	for(int i=0;i<n;++i)
	{
		int t=sum[i]+MAXN;
		if(f[t]==-1) f[t]=cow[i+1].x;
		else ans=std::max(ans,cow[i].x-f[t]);
	}
	printf("%d\n",ans);
	return 0;
}

