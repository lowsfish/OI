#include<cstdio>
#include<cmath>
#include<cstring>
const int MAXN=1000+5;
int gcd(int a,int b) {
	return b?gcd(b,a%b):a;
}
typedef long long LL;
LL lcm(int a,int b) {
	return a/gcd(a,b)*b;
}
int calc(int n) {
	static int yue[MAXN];
	int cnt=0;
	int s=sqrt((double)n)+1;
	for(int i=1;i<s;++i) if(n%i==0) {
		yue[cnt++]=i;
		if(i!=n/i) yue[cnt++]=n/i;
	}
	int ans=0;
	for(int i=0;i<cnt;++i)
		for(int j=0;j<cnt;++j) {
			if(yue[i]>yue[j]) continue;
			if(lcm(yue[i],yue[j])==n) ++ans;
		}
	return ans;
}
int n;
int main() {
	while(scanf("%d",&n)!=EOF && n)
		printf("%d %d\n",n,calc(n));
	return 0;
}
