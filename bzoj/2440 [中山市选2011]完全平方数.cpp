#include<cstdio>
const int MAXN=44726;
int mu[MAXN],prime[MAXN],tot;
bool not_prime[MAXN];
void pre_do()
{
	mu[1]=1;
	for(int i=2;i<MAXN;++i)
	{
		if(!not_prime[i]) mu[i]=-1,prime[tot++]=i;
		for(int j=0;prime[j]*i<MAXN;++j)
		{
			not_prime[prime[j]*i]=1;
			if(i%prime[j]==0)
			{
				mu[prime[j]*i]=0;
				break;
			}
			mu[prime[j]*i]=-mu[i];
		}
	}
}
int calc(int x)
{
	int ans=0;
	for(int i=1;i*i<=x;++i)
		ans+=x/(i*i)*mu[i];
	return ans;
}
int main()
{
	freopen("1.in","r",stdin);
	pre_do();
	int T;
	scanf("%d",&T);
	while(T--)
	{
		int k;
		scanf("%d",&k);
		int l=1,r=k*2+1;
		while(l+1<r)
		{
			int m=l+(r-l)/2;
			if(calc(m)>=k) r=m;
			else l=m;
		}
		if(calc(l)<k) l=r;
		printf("%d\n",l);
	}
	return 0;
}
