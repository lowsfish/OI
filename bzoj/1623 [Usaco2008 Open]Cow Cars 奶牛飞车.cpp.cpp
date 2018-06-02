#include<cstdio>
#include<algorithm>
const int MAXN=50000;
int s[MAXN];
int cnt[MAXN];
int n,m,d,l;
int main()
{
	scanf("%d%d%d%d",&n,&m,&d,&l);
	for(int i=0;i<n;++i) scanf("%d",s+i);
	std::sort(s,s+n);
	int p1=0,p2=0;
	while(s[p1]<l) ++p1;
	int ans=0;
	while(p1<n)
	{
		if(s[p1]-cnt[p2]*d>=l) ++ans,++cnt[p2++];
		++p1;
		if(p2==m) p2=0;
	}
	printf("%d\n",ans);
	return 0;
}
