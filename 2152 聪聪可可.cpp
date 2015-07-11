#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
const int MAX_N = 20000 + 5;
const int INF = ~0U >> 1;
struct Edge {
	int v, c;
	Edge(int v, int c):v(v), c(c) {}
};
using std::vector;
typedef std::pair<int, int> PII;
typedef vector<Edge>::iterator vit;
vector<Edge> G[MAX_N];
bool centroid[MAX_N];
int size[MAX_N];
int get_size(int u, int fa) {
	size[u] = 1;
	for (vit e = G[u].begin(); e != G[u].end(); ++e)
		if (e->v != fa && !centroid[e->v])
			size[u] += get_size(e->v, u);
	return size[u];
}
PII get_centroid(int u, int fa, int sum) {
	PII ans(INF, 0);
	int t = 0;
	for (vit e = G[u].begin(); e != G[u].end(); ++e)
		if (e->v != fa && !centroid[e->v]) {
			ans = std::min(ans, get_centroid(e->v, u, sum));
			t = std::max(t, size[e->v]);
		}
	t = std::max(t, sum - t);
	return ans = std::min(ans, PII(t, u));
}
int d[MAX_N], num[3];
void get_dist(int u, int fa) {
	num[d[u]]++;
	for (vit e = G[u].begin(); e != G[u].end(); ++e)
		if (e->v != fa && !centroid[e->v]) {
			d[e->v] = (d[u] + e->c) % 3;
			get_dist(e->v, u);
		}
}
int calc(int u, int now) {
	memset(num, 0, sizeof num);
	d[u] = now % 3;
	get_dist(u, -1);
	return num[1] * num[2] * 2 + num[0] * num[0];
}
int ans = 0;
void solve(int u) {
	get_size(u, -1);
	int s = get_centroid(u, -1, size[u]).second;
	centroid[s] = true;
	ans += calc(s, 0);
	for (vit e = G[s].begin(); e != G[s].end(); ++e)
		if (!centroid[e->v]) {
			ans -= calc(e->v, e->c);
			solve(e->v);
		}
}
int n;
int gcd(int a, int b) {
	return b ? gcd(b, a % b) : a;
}
int main() {
	scanf("%d", &n);
	for (int i = 0; i < n - 1; ++i) {
		int u, v, c;
		scanf("%d%d%d", &u, &v, &c);
		G[u].push_back(Edge(v, c % 3));
		G[v].push_back(Edge(u, c % 3));
	}
	solve(1);
	int t = gcd(ans, n * n);
	printf("%d/%d\n", ans / t, n * n / t);
}
