#include<cstdio>
#include<algorithm>
typedef long long LL;
LL cnt[15][10];
int src(int i,int j)		//长度i最高位j
{
	if(i==1) return 1;
	int& ans=cnt[i][j];
	if(ans>0) return ans;
	for(int k=0;k<10;++k) if(abs(k-j)>=2) ans+=src(i-1,k);
}
int N[15],n;
LL ans;

