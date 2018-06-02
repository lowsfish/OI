#include<cstdio>
#include<cstring>
const int MAXN = 500 + 5;
typedef long long LL;

struct Matrix {
	int n, m;
	int A[MAXN][MAXN];
	Matrix(int n, int m):n(n), m(m) { memset(A, 0, sizeof A); }
};

int MOD;
Matrix operator*(Matrix A, Matrix B) {
	int n = A.n, m = A.m, p = B.m;
	Matrix ans(n, p);
	if(n == m && n == p) {
		for (int j = 0; j < p; ++j)
			for (int k = 0; k < m; ++k)
				(ans.A[0][j] += (LL)A.A[0][k] * B.A[j][k] % MOD) %= MOD;
		for (int i = 1; i < n; ++i)
			for (int j = 0; j < p; ++j) {
				if (j == 0) ans.A[i][j] = ans.A[i - 1][n - 1];
				else ans.A[i][j] = ans.A[i - 1][j - 1];
			}
	}
	else {
		for (int i = 0; i < n; ++i)
			for (int j = 0; j < p; ++j)
				for(int k = 0; k < m; ++k)
					(ans.A[i][j] += (LL)A.A[i][k] * B.A[k][j] % MOD) %= MOD;
	}
	return ans;
}

Matrix base(int n) {
	Matrix ans(n, n);
	for (int i = 0; i < n; ++i) ans.A[i][i] = 1;
	return ans;
}

Matrix Mpow(Matrix A, int b) {
	Matrix ans = base(A.n);
	for(; b; b >>= 1, A = A * A)
		if (b & 1) ans = ans * A;
	return ans;
}

int n, d, k;
int main() {
	scanf("%d%d%d%d", &n, &MOD, &d, &k);
	Matrix A(n, n);
	for (int i = 0; i < n; ++i) {
		for (int j = i; j <= i + d; ++j)
			A.A[i][j % n] = 1;
		for (int j = i - 1; j >= i - d; --j)
			A.A[i][(j + n) % n] = 1;
	}
	A = Mpow(A, k);
	Matrix B(1, n);
	for (int i = 0; i < n; ++i) scanf("%d", &B.A[0][i]);
	B = B * A;
	for (int i = 0; i < n; ++i)
		printf("%d%c", B.A[0][i], i == n - 1 ? '\n' : ' ');
	return 0;
}
