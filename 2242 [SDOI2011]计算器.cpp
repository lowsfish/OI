#include<cstdio>
#include<cmath>
#include<map>
#include<algorithm>
#define fail puts("Orz, I cannot find x!")
typedef long long LL;
int T,k;
int pow_mod(LL a,LL b,int MOD)
{
	LL ans=1;
	for(a%=MOD;b;b>>=1,a=a*a%MOD)
		if(b&1) ans=ans*a%MOD;
	return ans;
}
int gcd(int a,int b)
{
	return b==0?a:gcd(b,a%b);
}
std::map<int,int> mp;
int bsgs(int y,int z,int MOD)
{
	y%=MOD;z%=MOD;
	if(!y && !z) return 1;
	if(!y) return -1;
	mp.clear();
	int m=sqrt(MOD)+1,t=1;
	mp[1]=m+1;
	for(int i=1;i<m;++i)
	{
		t=(LL)t*y%MOD;
		if(!mp.count(t)) mp[t]=i;
	}
	int tmp=pow_mod(y,MOD-m-1,MOD),ine=1;
	for(int k=0;k<m;++k)
	{
		int i=mp[(LL)z*ine%MOD];
		if(i)
		{
			if(i==m+1) i=0;
			return k*m+i;
		}
		ine=(LL)ine*tmp%MOD;
	}
	return -1;
}
int main()
{
	scanf("%d%d",&T,&k);
	while(T--)
	{
		int y,z,p;
		scanf("%d%d%d",&y,&z,&p);
		if(k==1) printf("%d\n",pow_mod(y,z,p));
		else if(k==2)
		{
			int d=gcd(y,p);
			if(z%d) fail;
			else
			{
				y/=d;z/=d;p/=d;
				int x=pow_mod(y,p-2,p);
				x=(LL)x*z%p;
				printf("%d\n",x);
			}
		}
		else
		{
			int t=bsgs(y,z,p);
			if(t==-1) fail;
			else printf("%d\n",t);
		}
	}
	return 0;
}
