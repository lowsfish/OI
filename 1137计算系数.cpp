#include<iostream>
#include<cstdio>
using namespace std;
const int MOD=10007;
const int MAXN=1000+5;
#define int long long
int C[MAXN][MAXN];
int a,b,k,n,m;
int pow(int a,int b)
{
	int base=a,ans=1;
	while(b)
	{
		if(b&1) ans=ans*base%MOD;
		base=base*base%MOD;
		b>>=1;
	}
	return ans;
}
#undef int
int main()
{
	cin>>a>>b>>k>>n>>m;
	for(int i=1;i<=k;++i) C[i][0]=1,C[i][1]=i;
	for(int i=2;i<=k;++i)
		for(int j=1;j<=i;++j)
		{
			C[i][j]=C[i-1][j]+C[i-1][j-1];
			C[i][j]%=MOD;
		}
	cout<<C[k][m]*pow(a,n)%MOD*pow(b,m)%MOD<<endl;
	return 0;
}
