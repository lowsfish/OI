#include<cstdio>
#include<algorithm>
const int MAXN=20000+5;
int n,m;
int a[MAXN],b[MAXN];
int main()
{
	while(scanf("%d%d",&n,&m)!=EOF && n)
	{
		for(int i=0;i<n;++i) scanf("%d",a+i);
		for(int i=0;i<m;++i) scanf("%d",b+i);
		std::sort(a,a+n);std::sort(b,b+m);
		int p1=0,p2=0,ans=0;
		while(p1<n && p2<m)
		{
			if(b[p2]>=a[p1]) ans+=b[p2],p1++,p2++;
			else p2++;
		}
		if(p1==n) printf("%d\n",ans);
		else printf("Loowater is doomed!\n");
	}
	return 0;
}
