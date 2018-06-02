#include <cstdio>
#include <algorithm>
#include <cstring>
const int MAX_N = 20000 + 5;
const int MOD = 1000;
int n;
int pa[MAX_N], d[MAX_N];
void init() {
	for (int i = 1; i <= n; ++i)
		pa[i] = i;
	memset(d, 0, sizeof d);
}
int find(int x) {
	if (pa[x] != x) {
		int root = find(pa[x]);
		d[x] += d[pa[x]];
		return pa[x] = root;
	}
	else return x;
}
int main() {
	int T;
	for (scanf("%d", &T); T--; ) {
		scanf("%d", &n);
		init();
		char s[2];
		while (scanf("%s", s) == 1 && s[0] != 'O') {
			if (s[0] == 'I') {
				int u, v;
				scanf("%d%d", &u, &v);
				pa[u] = v;
				d[u] = std::abs(u - v) % MOD;
			}
			else {
				int u;
				scanf("%d", &u);
				find(u);
				printf("%d\n", d[u]);
			}
		}
	}
}
