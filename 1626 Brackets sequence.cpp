#include<cstdio>
#include<algorithm>
#include<cstring>
const int MAXN=100+5;
const int INF=1<<29;
int T,n;
char s[MAXN];
int dp[MAXN][MAXN];
inline bool match(char a,char b)
{
	if((a=='(' && b==')') || (a=='[' && b==']')) return 1;
	return 0;
}
/*int src(int i,int j)
{
	if(j<i) return 0;
	if(dp[i][j]>0) return dp[i][j];
	if(i==j) return dp[i][j]=1;
	int ans=INF;
	if(match(s[i],s[j])) ans=src(i+1,j-1);
	for(int k=i;k<j;++k)
		ans=std::min(ans,src(i,k)+src(k+1,j));
	return dp[i][j]=ans;
}*/
void dpdp()
{
	for(int i=0;i<n;++i) dp[i][i]=1,dp[i+1][i]=0;
	for(int i=n-2;i>=0;--i)
		for(int j=i+1;j<n;++j)
		{
			if(match(s[i],s[j])) dp[i][j]=dp[i+1][j-1];
			else dp[i][j]=INF;
			for(int k=i;k<j;++k)
				dp[i][j]=std::min(dp[i][j],dp[i][k]+dp[k+1][j]);
		}
}
void print(int i,int j)
{
	if(j<i) return;
	if(dp[i][j]==0)
	{
		for(int k=i;k<=j;++k) putchar(s[k]);
		return;
	}
	if(i==j)
	{
		if(s[i]==')' || s[i]=='(') printf("()");
		else printf("[]");
		return;
	}
	int ans=dp[i][j];
	if(match(s[i],s[j]) && ans==dp[i+1][j-1])
	{
		putchar(s[i]);
		print(i+1,j-1);
		putchar(s[j]);
		return;
	}
	for(int k=i;k<j;++k) if(dp[i][k]+dp[k+1][j]==ans)
	{
		print(i,k);
		print(k+1,j);
		return;
	}
}
inline void readline()
{
	fgets(s,MAXN,stdin);
}
int main()
{
	//freopen("1.in","r",stdin);
	scanf("%d",&T);
	getchar();
	readline();
	while(T--)
	{
		readline();
		n=strlen(s)-1;
		memset(dp,0,sizeof(dp));
		dpdp();
		print(0,n-1);
		putchar(10);
		if(T) putchar(10);
		readline();
	}
	return 0;
}
