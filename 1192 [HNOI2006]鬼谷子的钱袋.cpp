#include<cstdio>
int main()
{
	int n,cnt=0;
	scanf("%d",&n);
	while((1<<cnt)<=n) ++cnt;
	printf("%d\n",cnt);
	return 0;
}
