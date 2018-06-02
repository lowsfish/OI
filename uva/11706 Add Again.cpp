#include<cstdio>
#include<cstring>
#include<iostream>
#include<vector>
using std::vector;
using std::endl;
using std::cin;
using std::cout;
int dig[10];
int n;
typedef unsigned long long ULL;
ULL fac[13];
void init() {
	fac[0]=1;
	for(int i=1;i<=12;++i) fac[i]=fac[i-1]*i;
}
ULL ans[20];
ULL work() {
	ULL ans=0;
	for(int i=0;i<=9;++i) if(dig[i]) {
		ULL t=fac[n-1];
		for(int j=0;j<=9;++j)
			if(i!=j) t/=fac[dig[j]];
			else t/=fac[dig[j]-1];
		ans+=t*i;
	}
	return ans;
}
int main() {
//	freopen("1.in","r",stdin);
	init();
	while(scanf("%d",&n)!=EOF && n) {
		memset(dig,0,sizeof dig);
		memset(ans,0,sizeof ans);
		for(int i=0;i<n;++i) {
			int t;
			scanf("%d",&t);
			++dig[t];
		}
		ULL sum=work(),ans=0;
		for(int i=0;i<n;++i) {
			ans+=sum;
			sum*=10;
		}
		cout<<ans<<endl;
	}
	return 0;
}
