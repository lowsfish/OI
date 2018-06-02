#include<cstdio>
#include<algorithm>
typedef long long LL;
LL cnt[12][10],ans;
int N[12],n;
void pre_do()
{
	for(int i=0;i<10;++i) cnt[1][i]=1;
	for(int i=2;i<12;++i)
		for(int j=0;j<10;++j)
			for(int k=0;k<10;++k)
				if(abs(k-j)>=2) cnt[i][j]+=cnt[i-1][k];
}
void get(int x)
{
	if(!x) return;
	get(x/10);
	N[n++]=x%10;
}
void work(int p,int last)
{
	int t=N[p];
	if(p==n-1) 
	{
		for(int i=0;i<=t;++i) 
			if(abs(i-last)>=2) ++ans;
		return;
	}
	for(int i=0;i<t;++i) if(abs(i-last)>=2)
	{
		if(p==0 && i==0)
		{
			for(int j=1;j<n;++j)
				for(int k=1;k<=9;++k)
					ans+=cnt[j][k];
		}
		else
			ans+=cnt[n-p][i];
	}
	if(abs(t-last)>=2) work(p+1,t);
}
LL cal(int x)
{
	if(!x) return 0;
	n=ans=0;
	get(x);
	work(0,20);
	return ans;
}
int main()
{
	pre_do();
	int a,b;
	scanf("%d%d",&a,&b);
	printf("%lld\n",cal(b)-cal(a-1));
	return 0;
}

