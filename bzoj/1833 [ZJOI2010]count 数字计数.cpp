#include<cstdio>
#include<cstring>
typedef long long LL;
LL ans[10],f[20];
int n,N[20];
LL ten_pow[20];
void get(LL x) {
	for(n=0;x;x/=10,++n)
		N[n]=x%10;
}
LL A[20],C[20];
LL pre[10];
void dfs(int p) {
	if(p<0) {
		for(int i=0;i<10;++i)
			C[i]+=pre[i];
		return;
	}
	int t=N[p];
	for(int i=0;i<t;++i) {
		LL num=ten_pow[p];
		if(p==n-1 && i==0) {
			for(int k=0;k<10;++k)
				C[k]+=f[p];
			for(int j=p-1;j>=0;--j) C[0]-=ten_pow[j];
		}
		else {
			++pre[i];
			for(int j=0;j<10;++j) C[j]+=pre[j]*num;
			--pre[i];num/=10;
			for(int j=0;j<10;++j) C[j]+=f[p];
		}
	}
	++pre[t];dfs(p-1);
}
void calc(LL x) {
	get(x);
	memset(C,0,sizeof C);
	memset(pre,0,sizeof pre);
	dfs(n-1);
}
int main() {
	ten_pow[0]=1;
	for(int i=1;i<=12;++i) ten_pow[i]=ten_pow[i-1]*10;
	f[1]=1;
	for(int i=2;i<=12;++i) f[i]=f[i-1]*10+ten_pow[i-1];
	LL a,b;
	scanf("%lld%lld",&a,&b);
	calc(b);
	for(int i=0;i<10;++i) A[i]=C[i];
	calc(a-1);
	for(int i=0;i<10;++i) A[i]-=C[i];
	for(int i=0;i<10;++i) printf("%lld%c",A[i],i==9?'\n':' ');
	return 0;
}
