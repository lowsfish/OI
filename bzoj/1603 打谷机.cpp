#include<cstdio>
int n,t,ans;
int main()
{
	scanf("%d",&n);
	for(int i=0;i<n-1;++i)
	{
		scanf("%d%d%d",&t,&t,&t);
		ans^=t;
	}
	printf("%d\n",ans);
	return 0;
}
