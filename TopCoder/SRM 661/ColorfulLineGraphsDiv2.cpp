#include <cstdio>
#include <cmath>
#include <cstring>
#include <ctime>
#include <stack>
#include <queue>
#include <cctype>
#include <iomanip>
#include <string>
#include <bitset>
#include <iostream>
#include <algorithm>
#include <set>
#include <map>
#include <vector>
#include <sstream>
#include <typeinfo>
#include <fstream>
using namespace std;

const int MAXN=100+5;
const int MOD=1000000007;
typedef long long LL;
int n,k;
namespace work1
{
	int dp[MAXN][MAXN][MAXN];
	int src(int n,int a,int b)
	{
		int& ans=dp[n][a][b];
		if(ans!=-1) return ans;
		if(n==1) return ans=1;
		ans=0;
		if(a!=0)
		{
			LL t=src(n-1,a-1,b);
			(t*=n-a+1)%=MOD;
			(ans+=t)%=MOD;
		}
		if(b!=0)
		{
			LL t=src(n-1,a,b-1);
			(t*=n-b+1)%=MOD;
			(ans+=t)%=MOD;
		}
		if(n-a-b!=0)
		{
			LL t=src(n-1,a,b);
			(t*=a+b+1)%=MOD;
			(ans+=t)%=MOD;
		}
		return ans;
	}
	int work()
	{
		memset(dp,-1,sizeof dp);
		int ans=0;
		for(int i=0;i<=n;++i)
			for(int j=0;i+j<=n;++j)
				(ans+=src(n,i,j))%=MOD;
		return ans;
	}
};
namespace work2{
	int dp[MAXN][MAXN];
	int src(int n,int a)
	{
		int& ans=dp[n][a];
		if(ans!=-1) return ans;
		if(n==1) return ans=1;
		ans=0;
		if(a>0)
		{
			LL t=src(n-1,a-1);
			(t*=n-a+1)%=MOD;
			(ans+=t)%=MOD;
		}
		if(n-a>0)
		{
			LL t=src(n-1,a);
			(t*=a+1)%=MOD;
			(ans+=t)%=MOD;
		}
		return ans;
	}
	int work()
	{
		memset(dp,-1,sizeof dp);
		int ans=0;
		for(int i=0;i<=n;++i) (ans+=src(n,i))%=MOD;
		return ans;
	}
};
class ColorfulLineGraphsDiv2 {
    public:
    int countWays(int N, int K) {
		n=N;k=K;
		if(k==1) return 1;
		if(k==2) return work2::work();
		return work1::work();
    }
};

