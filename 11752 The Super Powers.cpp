#include<cstdio>
#include<cstring>
#include<set>
#include<cmath>
#include<iostream>
using std::cin;
using std::cout;
using std::endl;
typedef unsigned long long ULL;
const int MAXN=100+5;
ULL INF=~0ULL;
std::set<ULL> st;
bool vis[MAXN];
int prime[MAXN],tot_prime;
void sieve() {
	for(int i=2;i<=8;++i) if(!vis[i])
		for(int j=i*i;j<MAXN;j+=i) vis[j]=1;
	for(int i=2;i<MAXN;++i) if(!vis[i])
		prime[tot_prime++]=i;
}
ULL Pow(ULL a,int b) {
	ULL ans=1;
	for(;b;b>>=1,a*=a)
		if(b&1) ans*=a;
	return ans;
}
int main() {
	sieve();
	for(int i=2;i<(1<<16);++i) {
		int maxe=ceil(log((double)INF)/log(double(i)));
		for(int j=0;j<maxe;++j) if(vis[j])
			st.insert(Pow(i,j));
	}
	st.insert(1);
	for(std::set<ULL>::iterator it=st.begin();it!=st.end();++it)
		cout<<*it<<endl;
	return 0;
}
