#include<cstdio>
int T,G,L;
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d",&G,&L);
		if(L%G) printf("-1\n");
		else printf("%d %d\n",G,L);
	}
	return 0;
}
