#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
const int MAX_N = 50000 + 5;
const int MAX_M = 200000 + 5;
const int MAX_C = 1000000 + 5;
inline int lowbit(int x) {
	return x & -x;
}
struct BIT {
	int A[MAX_N], n;
	void set(int _n) {
		n = _n;
		for (int i = 1; i <= n; ++i)
			A[i] = 0;
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
} T;
struct Node{
	int r, id;
	Node(int r, int id):r(r), id(id) {}
};
std::vector<Node> ask[MAX_N];
typedef std::vector<Node>::iterator vit;
int a[MAX_N], n, m, ans[MAX_M], p[MAX_C], next[MAX_N];
bool used[MAX_C];
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) scanf("%d", a + i);
	T.set(n);
	scanf("%d", &m);
	for (int i = 0; i < m; ++i) {
		int l, r;
		scanf("%d%d", &l, &r);
		ask[l].push_back(Node(r, i));
	}
	memset(p, -1, sizeof p);
	for (int i = n; i >= 1; --i)
		next[i] = p[a[i]], p[a[i]] = i;
	for (int i = 1; i <= n; ++i) if (!used[a[i]])
		used[a[i]] = true, T.update(i, 1);
	for (int i = 1; i <= n; ++i) {
		for (vit it = ask[i].begin(); it != ask[i].end(); ++it)
			ans[it->id] = T.get_sum(it->r) - T.get_sum(i - 1);
		if (~next[i]) T.update(next[i], 1);
	}
	for (int i = 0; i < m; ++i)
		printf("%d\n", ans[i]);
}
