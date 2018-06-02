#include<cstdio>
#include<cstring>
#include<algorithm>
#include<string>
#include<iostream>
#include<sstream>
using namespace std;
const int MAXS=8;
const int MAXN=100+20+5;;
const int INF=1<<29;
int m,n,s,c[MAXN],st[MAXN],dp[MAXN][1<<MAXS][1<<MAXS];
string input;
int src(int i,int s0,int s1,int s2)
{
	if(i==m+n) return s2==(1<<s)-1?0:INF;
	int &ans=dp[i][s1][s2];
	if(ans>=0) return ans;
	ans=INF;
	if(i>=m) ans=src(i+1,s0,s1,s2);
	int m0=st[i]&s0,m1=st[i]&s1;
	s0^=m0;s1=(s1^m1)|m0;s2|=m1;
	ans=min(ans,c[i]+src(i+1,s0,s1,s2));
	return ans;
}
int main()
{
	//freopen("1.in","r",stdin);
	while(scanf("%d%d%d",&s,&m,&n)!=EOF && s)
	{
		cin.get();
		memset(dp,-1,sizeof(dp));
		memset(st,0,sizeof(st));
		for(int i=0;i<m+n;++i)
		{
			getline(cin,input);
			stringstream ss(input);
			ss>>c[i];
			int t;
			while(ss>>t) st[i]|=(1<<(t-1));
		}
		printf("%d\n",src(0,(1<<s)-1,0,0));
	}
	return 0;
}
