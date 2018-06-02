#include<cstdio>
#include<cstring>
const int MOD=1000000007;
const int MAXN=1000000+5;
char s[MAXN];
int n;
int f[MAXN],cnt[MAXN];
void work()
{
	int j=0;
	cnt[1]=1;
	for(int i=2;i<=n;++i)
	{
		while(j && s[i]!=s[j+1]) j=f[j];
		if(s[i]==s[j+1]) ++j;
		f[i]=j;
		cnt[i]=cnt[j]+1;	//变到0需要走几次
	}
	j=0;
	long long ago=1;
	for(int i=2;i<=n;++i)
	{
		while(j && s[j+1]!=s[i]) j=f[j];
		if(s[j+1]==s[i]) ++j;
		while((j<<1)>i) j=f[j];
		ago*=cnt[j]+1;
		ago%=MOD;
	}
	printf("%lld\n",ago);
}
int main()
{
	int T;
	scanf("%d",&T);
	while(T--)
	{
		scanf("%s",s+1);
		n=strlen(s+1);
		work();
	}
	return 0;
}
