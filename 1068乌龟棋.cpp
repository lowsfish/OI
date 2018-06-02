#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#define MAXN 400
#define MAXSZ 50
using namespace std;
int dp[MAXSZ][MAXSZ][MAXSZ][MAXSZ];
int seg[MAXN];

inline int step(int i,int j,int k,int l)
{
	return i+j*2+k*3+l*4+1;
}
int main()
{
	//freopen("1.in","r",stdin);
	int N,M,i,f[5]={0},j,k,l;
	cin>>N>>M;
	for(i=1;i<=N;++i) cin>>seg[i];
	for(i=0;i<M;++i)
	{
		cin>>k;
		f[k]++;
	}
	dp[0][0][0][0]=seg[1];
	for(i=0;i<=f[1];++i)
	for(j=0;j<=f[2];++j)
	for(k=0;k<=f[3];++k)
	for(l=0;l<=f[4];++l)
	{
		int &state=dp[i][j][k][l];
		int score=seg[step(i,j,k,l)];
		if(i>0) state=max(state,dp[i-1][j][k][l]+score);
		if(j>0) state=max(state,dp[i][j-1][k][l]+score);
		if(k>0) state=max(state,dp[i][j][k-1][l]+score);
		if(l>0) state=max(state,dp[i][j][k][l-1]+score);
	}
	cout<<dp[f[1]][f[2]][f[3]][f[4]]<<endl;
	return 0;
}
