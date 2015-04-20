#include<cstdio>
const int MAXN=50000+5;
int n,m;
int a[MAXN],stk[MAXN];
int top;
int main()
{
	//freopen("1.in","r",stdin);
	scanf("%d%d",&n,&m);
	for(int i=0;i<n;++i) scanf("%d%d",a+i,a+i);
	int ans=n;
	for(int i=0;i<n;++i)
	{
		while(top && stk[top-1]>a[i]) --top;
		if((top || !a[i]) && stk[top-1]==a[i]) --ans;
		else stk[top++]=a[i];
	}
	printf("%d\n",ans);
	return 0;
}

