#include <cstdio>
const int MAXN = 100 + 5;
int n, m;
double c[MAXN][MAXN];
int a[MAXN];
void pre_do() {
	for (int j = 0; j < n; ++j)
		for (int i = 0; i + j < n; ++i) {
			if (j == 0) c[i][i + j] = a[i];
			else c[i][i + j] = (c[i + 1][i + j] - c[i][i + j - 1]) / j;
		}
}
double calc(double x) {
	double ans = 0.0, t = 1.0;
	for (int i = 0; i < n; ++i) {
		ans += c[0][i] * t;
		t *= (x - i - 1);
	}
	return ans;
}
int main() {
	int T;
	scanf("%d", &T);
	while (T--) {
		scanf("%d%d", &n, &m);
		for (int i = 0; i < n; ++i) scanf("%d", a + i);
		pre_do();
		for (int i = n + 1; i <= n + m; ++i)
			printf("%d%c", (int)(calc(i) + 1e-9), i == n + m ? '\n' : ' ');
	}
	return 0;
}
