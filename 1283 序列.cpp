#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>
const int INF = ~0U >> 2;
const int MAXN = 1000 * 2 + 5;
using std::max;
using std::min;
using std::vector;
using std::queue;
using std::priority_queue;
using std::fill;
typedef vector<int>::iterator vit;
struct MCMF {
	struct Edge {
		int from, to, cap, flow, cost;
		Edge(int from, int to, int cap, int flow, int cost):
			from(from), to(to), cap(cap), flow(flow), cost(cost) {}
	};
	int n, m, s, t;
	vector<Edge> edges;
	vector<int> G[MAXN];
	bool inq[MAXN];
	int d[MAXN], p[MAXN], a[MAXN];
	inline void add_edge(int from, int to, int cap, int cost) {
		edges.push_back(Edge(from, to, cap, 0, cost));
		edges.push_back(Edge(to, from, 0, 0, -cost));
		m = edges.size();
		G[from].push_back(m - 2);
		G[to].push_back(m - 1);
	}
	bool spfa(int& flow, int& cost) {
		queue<int> que;
		fill(d, d + n, -1);
		fill(inq, inq + n, 0);
		que.push(s);
		d[s] = 0; inq[s] = 1; p[s] = 0; a[s] = INF;
		while (!que.empty()) {
			int u = que.front(); que.pop();
			inq[u] = false;
			for (vit i = G[u].begin(); i != G[u].end(); ++i) {
				Edge& e = edges[*i];
				if (e.cap > e.flow && d[e.to] < d[u] + e.cost) {
					d[e.to] = d[u] + e.cost;
					p[e.to] = *i;
					a[e.to] = min(a[u], e.cap - e.flow);
					if(!inq[e.to]) que.push(e.to), inq[e.to] = true;
				}
			}
		}
		if (d[t] == -1) return false;
		flow += a[t];
		cost += a[t] * d[t];
		int u = t;
		while (u != s) {
			edges[p[u]].flow += a[t];
			edges[p[u] ^ 1].flow -= a[t];
			u = edges[p[u]].from;
		}
		return true;
	}
	int maxcost(int _s, int _t, int k) {
		s = _s; t = _t;
		int flow = 0, cost = 0;
		for (int i = 0; i < k; ++i) spfa(flow, cost);
		return cost;
	}
	void init(int _n) {
		n = _n;
		edges.clear();
		for (int i = 0; i < n; ++i) G[i].clear();
	}
}S;
int n, m, k;
int a[MAXN >> 1];
int main() {
	scanf("%d%d%d", &n, &m, &k);
	for (int i = 1; i <= n; ++i) scanf("%d", a + i);
	int s = 0, t = 2 * n + 1;
	S.init(2 * n + 2);
	for (int i = 1; i <= n; ++i) S.add_edge(s, i, INF, 0);
	for (int i = 1; i < n; ++i) S.add_edge(i, i + 1, INF, 0);
	for (int i = 1; i <= n; ++i) S.add_edge(i, i + n, 1, a[i]);
	for (int i = 1; i + m <= n; ++i)
		S.add_edge(i + n, i + m, INF, 0);
	for (int i = 1; i <= n; ++i)
		S.add_edge(i + n, t, INF, 0);
	printf("%d\n", S.maxcost(s, t, k));
}
