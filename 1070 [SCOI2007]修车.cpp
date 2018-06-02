#include<cstdio>
#include<algorithm>
#include<cstring>
#include<vector>
#include<queue>
const int MAXN = 60 * 9 + 60 + 5;
const int INF=~0U>>1;
struct Edge {
	int from, to, cap, flow, cost;
	Edge(int from, int to, int cap, int flow, int cost)
		:from(from), to(to), cap(cap), flow(flow), cost(cost) {}
};
using std::vector;
using std::fill;
using std::min;
struct MCMF {
	int n, m, s, t;
	vector<Edge> edges;
	vector<int> G[MAXN];
	int a[MAXN], p[MAXN], d[MAXN];
	bool inq[MAXN];
	void init(int _n) {
		n = _n;
		edges.clear();
		for(int i = 0; i < n; ++i) G[i].clear();
	}
	void addEdge(int from, int to, int cap, int cost) {
		edges.push_back(Edge(from, to, cap, 0, cost));
		edges.push_back(Edge(to, from, 0, 0, -cost));
		m = edges.size();
		G[from].push_back(m-2);
		G[to].push_back(m-1);
	}
	bool spfa(int& flow, int& cost) {
		fill(d, d + n, INF);
		fill(inq, inq + n, 0);
		std::queue<int> que;
		que.push(s);
		inq[s] = 1; d[s] = 0; p[s] = 0; a[s] = INF;
		while(!que.empty()) {
			int u = que.front(); que.pop();
			inq[u] = 0;
			for(vector<int>::iterator i = G[u].begin(); i != G[u].end(); ++i) {
				Edge& e=edges[*i];
				if(e.cap > e.flow && d[e.to] > d[u] + e.cost) {
					d[e.to] = d[u] + e.cost;
					p[e.to] = *i;
					a[e.to] = min(a[u], e.cap - e.flow);
					if(!inq[e.to]) inq[e.to] = 1, que.push(e.to);
				}
			}
		}
		if(d[t] == INF) return 0;
		flow += a[t];
		cost += d[t] * a[t];
		int u=t;
		while(u != s) {
			edges[p[u]].flow += a[t];
			edges[p[u]^1].flow -= a[t];
			u = edges[p[u]].from;
		}
		return 1;
	}
	int mincost(int _s, int _t) {
		s = _s; t = _t;
		int flow = 0,cost = 0;
		while(spfa(flow, cost));
		return cost;
	}
}S;
int n, m;
int time[65][15];
int main() {
	scanf("%d%d", &m, &n);
	S.init(n * m + n + 2);
	for(int i = 0; i < n; ++i)
		for(int j = 0; j < m; ++j)
			scanf("%d", &time[i][j]);
	for(int i = 0; i < m; ++i)
		for(int j = 0; j < n; ++j)
			for(int k = 0; k < n; ++k)
				S.addEdge(i * n + j, k + n * m, 1, (j+1) * time[k][i]);
	int s = n * m + n, t = n * m + n + 1;
	for(int i = 0; i < n * m; ++i)
		S.addEdge(s, i, 1, 0);
	for(int i = n * m; i < n * m + n; ++i)
		S.addEdge(i, t, 1, 0);
	printf("%.2f\n", (double)S.mincost(s, t) / n);
}
