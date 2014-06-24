#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
int tot=0;
int n,k;
int dp[250][10];
/*void dfs(int sum,int last,int cur)
{
	if(cur>k || sum>n) return;
	if(cur==k)
	{
		if(sum==n)
		{
			++tot;
			//for(int i=1;i<=k;++i) cout<<ans[i]<<' ';
			//cout<<endl;
		}
	}
	else
	{
		for(int i=last;i<=n;++i)
		{
			if(sum+i>n || (k-cur-1!=0 && (n-sum-i)/(k-cur-1)<1)) break;
			dfs(sum+i,i,cur+1);
		}
	}
}
*/
int main()
{
	freopen("1.in","r",stdin);
	cin>>n>>k;
	dp[0][0]=1;
	for(int i=1;i<=n;++i)
	{
		dp[i][1]=1;
	}
	for(int i=1;i<=n;++i)
		for(int j=1;j<=i&&j<=k;++j)
		{
			dp[i][j]=dp[i-j][j]+dp[i-1][j-1];
		}

	/*for(int i=1;i<=n/k;++i)
	{
		dfs(i,i,1);
	}
	cout<<tot<<endl;*/
	cout<<dp[n][k];
	return 0;
}
