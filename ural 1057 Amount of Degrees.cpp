#include<cstdio>
const int MAXN=32;
int f[MAXN][MAXN];
void init()
{
	f[0][0]=1;
	for(int i=1;i<MAXN;++i)
	{
		f[i][0]=f[i-1][0];
		for(int j=1;j<=i;++j)
			f[i][j]=f[i-1][j-1]+f[i-1][j];
	}
}
int tran(int x,int b)
{
	int s[101];
	int p=0;
	while(x)
	{
		s[p++]=x%b;
		x/=b;
	}
	for(int i=p-1;i>=0;--i) if(s[i]>1)
	{
		for(int j=i;j>=0;--j) s[j]=1;
		break;
	}
	int ans=0;
	for(int i=0;i<p;++i) if(s[i]) ans|=1<<i;
	return ans;
}
int cal(int x,int k)
{
	int tot=0,ans=0;
	for(int i=MAXN-1;i>=0;--i)
	{
		if(x&(1<<i))
		{
			++tot;
			if(tot>k) break;
			x^=1<<i;
		}
		if((1<<(i-1))<=x)
			ans+=f[i-1][k-tot];
	}
	if(tot+x==k) ++ans;
	return ans;
}
int k,b,x,y;
int main()
{
	scanf("%d%d%d%d",&x,&y,&k,&b);
	init();
	x=tran(x,b);y=tran(y,b);
	printf("%d\n",cal(y,k)-cal(x-1,k));
	return 0;
}
