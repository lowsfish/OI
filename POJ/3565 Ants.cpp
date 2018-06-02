#include<cstdio>
#include<cmath>
#include<vector>
#include<queue>
#include<algorithm>
using std::min;
using std::fill;
using std::vector;
const int MAXN = 100 * 2 + 5;
const int INF = ~0U >> 1;
struct Edge {
	int from, to, cap, flow;
	double cost;
	Edge(int from, int to, int cap, int flow, double cost)
		:from(from), to(to), cap(cap), flow(flow), cost(cost) {}
};
struct MCMF {
	int n, m, s, t;
	vector<Edge> edges;
	vector<int> G[MAXN];
	double d[MAXN];
	int a[MAXN], p[MAXN];
	bool inq[MAXN];
	int ans[MAXN >> 1];
	inline void add_edge(int from, int to, int cap, double cost) {
		edges.push_back(Edge(from, to, cap, 0, cost));
		edges.push_back(Edge(to, from, 0, 0, -cost));
		m = edges.size();
		G[from].push_back(m-2);
		G[to].push_back(m-1);
	}
	bool spfa(int& flow, double& cost) {
		fill(d, d + n, INF);
		fill(inq, inq + n, 0);
		std::queue<int> que;
		que.push(s);
		d[s] = 0; a[s] = INF; inq[s] = true;
		while(!que.empty()) {
			int u = que.front(); que.pop();
			inq[u] = false;
			for(vector<int>::iterator i = G[u].begin(); i != G[u].end(); ++i) {
				Edge& e=edges[*i];
				if(e.cap > e.flow && d[e.to] > d[u] + e.cost) {
					d[e.to] = d[u] + e.cost;
					p[e.to] = *i;
					a[e.to] = min(a[u], e.cap - e.flow);
					if(!inq[e.to]) inq[e.to] = true, que.push(e.to);
				}
			}
		}
		if(fabs(d[t] - INF) < 1e-10) return false;
		flow += a[t];
		cost += d[t] * a[t];
		int u = t;
		while(u != s) {
			edges[p[u]].flow += a[t];
			edges[p[u] ^ 1].flow -= a[t];
			u = edges[p[u]].from;
		}
		return true;
	}
	int mincost(int _s, int _t) {
		s = _s; t = _t;
		int flow = 0;
		double cost = 0;
		while(spfa(flow, cost));
		return cost;
	}
	void init(int _n) {
		n = _n;
		for(int i = 0; i < n; ++i) G[i].clear();
		edges.clear();
	}
	void show(int n) {
		for(vector<Edge>::iterator e = edges.begin(); e != edges.end(); ++e)
			if(e->flow == 1) {
				if(e->from == s || e->to == t) continue;
				ans[e->from] = e->to - n;
			}
		for(int i = 1; i <= n; ++i) printf("%d\n", ans[i]);
	}
}S;
int n;
typedef std::pair<int, int> Point;
#define x first
#define y second
Point A[MAXN >> 1], B[MAXN >> 1];
inline double sqr(double x) {
	return x * x;
}
inline double dist(Point A, Point B) {
	return sqrt(sqr(A.x - B.x) + sqr(A.y - B.y));
}
int main() {
	scanf("%d", &n);
	for(int i = 0; i < n; ++i) scanf("%d%d", &A[i].x, &A[i].y);
	for(int i = 0; i < n; ++i) scanf("%d%d", &B[i].x, &B[i].y);
	int s = 0, t = 2 * n + 1;
	S.init(2 * n + 2);
	for(int i = 0; i < n; ++i)
		for(int j = 0; j < n; ++j)
			S.add_edge(i + 1, j + n + 1, 1, dist(A[i], B[j]));
	for(int i = 0; i < n; ++i) S.add_edge(s, i + 1, 1, 0);
	for(int i = 0; i < n; ++i) S.add_edge(i + 1 + n, t, 1, 0);
	S.mincost(s, t);
	S.show(n);
	return 0;
} 
