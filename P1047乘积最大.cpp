#include<iostream>
#include<cstdio>
#include<cstring>
#define MAXSZ 50
#define MAXK 10
using namespace std;
typedef long long LL;
char s[MAXSZ];
int a[MAXSZ]={0};
LL sum[MAXSZ][MAXSZ]={0};
int n,k;
LL dp[MAXSZ][MAXK]={0};
char c;
int main()
{
	freopen("1.in","r",stdin);
	cin>>n>>k;
//	cin.getline(s+1,MAXSZ);
	for(int i=1;i<=n;++i)
	{
		cin>>c;
		a[i]=c-'0';
		sum[i][i]=a[i];
	}
//	for(int i=1;i<=n;++i) a[i]=s[i]-'0';

//	for(int i=1;i<=n;++i) sum[i][i]=a[i];
	for(int i=1;i<=n;++i)
		for(int j=i+1;j<=n;++j)
			sum[i][j]=sum[i][j-1]*10+a[j];
	for(int i=1;i<=n;++i)
		dp[i][0]=sum[1][i];
	
	for(int i=1;i<=n;++i)
		for(int j=1;j<=i+1;++j)
			for(int l=1;l<=i-1;++l)
			{
				dp[i][j]=max(dp[i][j],dp[l][j-1]*sum[l+1][i]);
			}
	cout<<dp[n][k];
	return 0;
}
