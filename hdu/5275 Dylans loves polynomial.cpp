#include <cstdio>
typedef long long LL;
const int MAXN  = 3000 + 5;
const int MOD = 1000000007;
int n;
int X[MAXN], Y[MAXN];
int c[MAXN][MAXN];
int inv[250005];
int pow_mod(LL a, int b) {
	LL ans = 1;
	for (a %= MOD; b; b >>= 1, (a *= a) %= MOD)
		if (b & 1) (ans *= a) %= MOD;
	return (int)ans;
}

void pre_do() {
	for (int i = 1; i <= 250000; ++i) inv[i] = pow_mod(i, MOD - 2);
	for (int j = 0; j < n; ++j)
		for (int i = 0; i + j < n; ++i) {
			if (j == 0) c[i][i + j] = Y[i];
			else if(X[i + j] > X[i]) c[i][i + j] = (LL) (c[i + 1][i + j] - c[i][i + j - 1] + MOD) % MOD *
						inv[X[i + j] - X[i]] % MOD;
			else c[i][i + j] = (LL) (-c[i + 1][i + j] + c[i][i + j - 1] + MOD) % MOD *
						inv[-X[i + j] + X[i]] % MOD;
		}
}

int calc(int l, int r, int x) {
	LL t = 1, ans = 0;
	for (int i = l; i <= r; ++i) {
		(ans += (LL) c[l][i] * t) %= MOD;
		(t *= ((x - X[i] + MOD) % MOD)) %= MOD;
	}
	return ans;
}
int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; ++i) scanf("%d%d", X + i, Y + i);
	pre_do();
	int nQ;
	scanf("%d", &nQ);
	while (nQ--) {
		int l, r, x;
		scanf("%d%d%d", &l, &r, &x);
		printf("%d\n", calc(l - 1, r - 1, x));
	}
	return 0;
}
