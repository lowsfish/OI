#include<cstdio>
#include<cstring>
#include<algorithm>
const int MAXL=300+5;
const int MAXN=600+5;
char dict[MAXN][30];
int l[MAXN];
char s[MAXL];
int n,len;
int dp[MAXL];
int cal(char* ss,char* t)
{
	int ans=0;
	while(*ss!=0)
	{
		if(*t==*ss) ++t;
		else ++ans;
		if(*t==0) return ans;
		++ss;
	}
	return -1;
}
int main()
{
	scanf("%d%d",&n,&len);
	scanf("%s",s);
	for(int i=0;i<n;++i) scanf("%s",dict[i]),l[i]=strlen(dict[i]);
	for(int i=len-1;i>=0;--i)
	{
		dp[i]=dp[i+1]+1;
		for(int j=0;j<n;++j)
		{
			int t=cal(s+i,dict[j]);
			if(t!=-1)
				dp[i]=std::min(dp[i],dp[i+l[j]+t]+t);
		}
	}
	printf("%d\n",dp[0]);
	return 0;
}
