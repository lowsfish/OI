#include<cstdio>
#include<algorithm>
#include<cstring>
const int MAXN=200000+20;
char dict[210][15];
int dp[MAXN];
int len[210];
char s[MAXN];
char t[100];
int sum;
int src(char* ss)
{
	if(dp[ss-s]>0) return dp[ss-s];
	int &ans=dp[ss-s];
	for(int i=0;i<sum;++i)
		if(strncmp(dict[i],ss,len[i])==0)
			ans=std::max(ans,src(ss+len[i])+len[i]);
	return ans;
}
int main()
{
	freopen("1.in","r",stdin);
	while(scanf("%s",dict[sum])==1)
	{
		if(dict[sum][0]=='.') break;
		len[sum]=strlen(dict[sum++]);
	}
	while(scanf("%s",t)==1)
	{
		strcat(s,t);
	}
	printf("%d\n",src(s));
	return 0;
}
