#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
using namespace std;
const int MAXN=200000+10;
typedef long long LL;
LL abs(LL a)
{
	if(a<0) a=-a;
	return a;
}
int n,m;
int w[MAXN],v[MAXN],maxw=0;
int seg[MAXN][2];
LL S,ans=1<<30;
LL getans(int M)
{
	LL res=0;
	LL s[MAXN]={0},cnt[MAXN]={0};
	for(int i=1;i<=n;++i)
	{
		if(w[i]>=M) s[i]=s[i-1]+v[i],cnt[i]=cnt[i-1]+1;		//维护前缀和
		else s[i]=s[i-1],cnt[i]=cnt[i-1];
	}
	for(int i=0;i<m;++i)
	{
		LL t=s[seg[i][1]]-s[seg[i][0]-1];
		t*=cnt[seg[i][1]]-cnt[seg[i][0]-1];
		res+=t;
	}
	//if(M==4) cout<<res<<endl;
	return res;
}
int main()
{
	//freopen("1.in","r",stdin);
	ans<<=31;
	scanf("%d%d",&n,&m);
	cin>>S;
	for(int i=1;i<=n;++i)
	{
		scanf("%d%d",w+i,v+i);
		maxw=max(maxw,w[i]);
	}
	for(int i=0;i<m;++i)
	{
		scanf("%d%d",&seg[i][0],&seg[i][1]);
	}
	int L=0,R=maxw+1;
	while(L<R)
	{
		int M=L+(R-L)/2;
		LL t=getans(M);
		ans=min(ans,abs(t-S));
		if(t>S) L=M+1;
		else R=M;
	}
	cout<<ans<<endl;
	return 0;
}
