#include<cstdio>
#include<cstring>
#include<cmath>
#define int LL
typedef long long LL;
const int MAXN = 200 + 5;
const int MAXM = 10000 + 5;
const int MAXK = 200 + 5;

int val[MAXN][MAXK];
int f[MAXN][MAXK];
int dp[MAXN][MAXK];
int n, m, K, MOD;
int hash[200005], cnt = 0;
int divs[MAXK];

void find_divisior() {
	memset(hash, -1, sizeof hash);
	for(int i = 1; i <= K; ++i) if(K % i == 0)
		hash[i] = cnt, divs[cnt++] = i;
}

LL gcd(LL a, LL b) {
	return b ? gcd(b, a % b) : a;
}
#undef int
int main() {
	scanf("%lld%lld%lld%lld", &n, &m, &K, &MOD);
	find_divisior();
	for(int i = 0; i < n; ++i)
		for(int j = 0; j < m; ++j) {
			int t;
			scanf("%d", &t);
			val[i][hash[gcd(K, t)]]++;
		}
	for(int i = 0; i < n; ++i)
		for(int j = 0; j < cnt; ++j) f[i][j] = val[i][j];
	for(int i = 1; i < n - 1; ++i)
		for(int j = 0; j < cnt; ++j)
			for(int k = j; k < cnt; ++k) {
				int t = hash[gcd(divs[j] * divs[k], K)];
				if(j == k) f[i][t] += val[i][j] * (val[i][j] - 1);
				else f[i][t] += val[i][j] * val[i][k] * 2;
				f[i][t] %= MOD;
			}
	for(int i = 0; i < cnt; ++i) dp[0][i] = val[0][i];
	for(int i = 0; i < n - 1; ++i)
		for(int j = 0; j < cnt; ++j)
			for(int k = 0; k < cnt; ++k) {
				int t = hash[gcd(divs[j] * divs[k], K)];
				dp[i + 1][t] += (dp[i][j] * f[i + 1][k]);
				dp[i + 1][t] %= MOD;
			}
	printf("%lld\n",dp[n - 1][cnt - 1]);
}
