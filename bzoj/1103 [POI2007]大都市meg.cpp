#include <cstdio>
#include <vector>
using std::vector;
const int MAX_N = 250000 + 5;
int L[MAX_N], R[MAX_N];
vector<int> G[MAX_N];
typedef vector<int>::iterator vit;
inline int lowbit(int x) {
	return x & -x;
}
struct BIT {
	int A[MAX_N << 1], n;
	void set (int _n) {
		n = _n;
		for (int i = 0; i <= n; ++i) A[i] = 0;
	}
	void update(int x, int add) {
		for (; x <= n; x += lowbit(x))
			A[x] += add;
	}
	int get_sum(int x) {
		int ans = 0;
		for (; x > 0; x -= lowbit(x))
			ans += A[x];
		return ans;
	}
}T;
int dfs_clock = 0;
int fa[MAX_N];
void dfs(int u) {
	L[u] = ++dfs_clock;
	for (vit e = G[u].begin(); e != G[u].end(); ++e) if (*e != fa[u])
		fa[*e] = u, dfs(*e);
	R[u] = ++dfs_clock;
}
int main() {
	int n;
	scanf("%d", &n);
	for (int i = 0; i < n - 1; ++i) {
		int a, b;
		scanf("%d%d", &a, &b);
		G[a].push_back(b);
		G[b].push_back(a);
	}
	T.set(n * 2);
	dfs(1);
	for (int i = 1; i <= n; ++i)
		T.update(L[i], 1), T.update(R[i], -1);
	int nQ;
	scanf("%d", &nQ);
	nQ += n - 1;
	while (nQ--) {
		char cmd[5];
		scanf("%s", cmd);
		if (cmd[0] == 'A') {
			int a, b;
			scanf("%d%d", &a, &b);
			T.update(L[b], -1);
			T.update(R[b], 1);
		}
		else {
			int a;
			scanf("%d", &a);
			printf("%d\n", T.get_sum(L[a]) - 1);
		}
	}
}
