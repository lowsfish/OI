#include<cstdio>
#include<algorithm>
const int MAXN=20;
int a[MAXN];
int n;
int now[MAXN>>1];
void dfs(int cur,int num)
{
	if(num==6)
	{
		for(int i=0;i<6;++i)
			printf("%d%c",now[i],i==5?'\n':' ');
		return;
	}
	for(int i=cur;i<n;++i)
	{
		now[num]=a[i];
		dfs(i+1,num+1);
	}
}
int main()
{
	while(scanf("%d",&n)!=EOF && n)
	{
		for(int i=0;i<n;++i) scanf("%d",a+i);
		std::sort(a,a+n);
		dfs(0,0);
		puts("");
	}
	return 0;
}
