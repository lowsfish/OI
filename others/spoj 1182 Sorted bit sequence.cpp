#include<cstdio>
int f[32][32];
void pre_do()
{
	f[0][0]=1;
	for(int i=1;i<=31;++i)
	{
		f[i][0]=1;
		for(int j=1;j<=i;++j) f[i][j]=f[i-1][j]+f[i-1][j-1];
	}
}
int calc(int x,int k)
{
	if(x<0) return 0;
	int tot=0,ans=0;
	for(int i=31;i>=0;--i)
	{
		if(x&(1U<<i))
		{
			if(++tot>k) break;
			x^=1U<<i;
		}
		if(x&(1<<(i-1)))
		{
			ans+=f[i-1][k-tot];
		}
	}
	if(x==0 && tot==k) ++ans;
	return ans;
}
int find(int x,int y,int k)
{
	if(k==0) return 0;
	int i;
	for(i=0;i<=31;++i)
	{
		int t=calc(y,i)-calc(x-1,i);
		if(k<=t) break;
		k-=t;
	}
	if(calc(x-1,i)-calc(x,i)==k) return x;
	int tmp=calc(x-1,i);
	while(x<y)
	{
		int mid=x+(y-x)/2;
		if(calc(mid,i)-tmp<k) x=mid+1;
		else y=mid;
	}
	return x;
}
int main()
{
	//freopen("1.in","r",stdin);
	pre_do();
	int T;
	scanf("%d",&T);
	while(T--)
	{
		int x,y,k;
		scanf("%d%d%d",&x,&y,&k);
		bool flag=0;
		if(y==0) --y,--k;
		if(x<0) flag=1,x^=1<<31,y^=1<<31;
		int ans=find(x,y,k);
		if(flag) ans^=1<<31;
		printf("%d\n",ans);
	}
	return 0;
}
