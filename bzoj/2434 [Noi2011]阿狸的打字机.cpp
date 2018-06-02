#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using std::vector;
const int MAX_N = 100000 + 5;
const int INF = ~0U >> 1;
inline int idx(char c) {
	return c - 'a';
}
struct Trie {
	static int numId;
	int id;
	Trie* ch[26], *fa, *fail;
	Trie(Trie* f):fa(f) {
		id = numId++;
		memset(ch, 0, sizeof ch);
		fail = NULL;
	}
	Trie* getch(char c) {
		int w = idx(c);
		if (!ch[w]) ch[w] = new Trie(this);
		return ch[w];
	}
};
Trie* root = new Trie(NULL);
int Trie::numId = 0;
char s[MAX_N];
int n, m, num = 0;
Trie* map[MAX_N];
struct Node {
	int x, id;
	Node(int x, int id):x(x), id(id) {}
};
vector<Node> Ask[MAX_N];
typedef vector<Node>::iterator it;
void input() {
	scanf("%s", s);
	n = strlen(s);
	Trie* t = root;
	for (int i = 0; i < n; ++i) {
		if (s[i] == 'P') map[++num] = t;
		else if (s[i] == 'B') {
			if (t->fa) t = t->fa;
		}
		else t = t->getch(s[i]);
	}
	scanf("%d", &m);
	for (int i = 0; i < m; ++i) {
		int x, y;
		scanf("%d%d", &x, &y);
		Ask[map[y]->id].push_back(Node(x, i));
	}
}
Trie* q[MAX_N];
int qh, qt;
void build() {
	qh = qt = 0;
	q[qt++] = root;
	while (qh < qt) {
		Trie* u = q[qh++];
		for (int i = 0; i < 26; ++i) if (u->ch[i]) {
			Trie* v= u->ch[i];
			Trie* p = u->fail;
			while (p && !p->ch[i]) p = p->fail;
			if (!p) v->fail = root;
			else v->fail = p->ch[i];
			q[qt++] = v;
		}
		else if (u->fail) u->ch[i] = u->fail->ch[i];
		else u->ch[i] = root;
	}
}
vector<int> G[MAX_N];
typedef vector<int>::iterator vit;
void build_gragh() {
	for (int i = 1; i < qt; ++i)
		G[q[i]->fail->id].push_back(q[i]->id);
}
int L[MAX_N], R[MAX_N];
int dfs_clock = 0;
void dfs(int u) {
	L[u] = ++dfs_clock;
	for (vit e = G[u].begin(); e != G[u].end(); ++e)
		dfs(*e);
	R[u] = ++dfs_clock;
}
struct BIT {
	int A[MAX_N << 1], n;
	inline int lowbit(int x) {
		return x & -x;
	}
	void set(int _n) {
		n = _n;
		for (int i = 1; i <= n; ++i) A[i] = 0;
	}
	void update(int x, int add) {
		for (; x <= n; x +=lowbit(x))
			A[x] += add;
	}
	int get_sum(int x) {
		int sum = 0;
		for (; x > 0; x -= lowbit(x))
			sum += A[x];
		return sum;
	}
}T;
int ans[MAX_N];
int main() {
	freopen("1.in", "r", stdin);
	input();
	build();
	build_gragh();
	dfs(0);
	Trie* t = root;
	T.set(n << 1);
	for (int i = 0; i < n; ++i) {
		if (s[i] == 'P')
			for (it j = Ask[t->id].begin(); j != Ask[t->id].end(); ++j)
				ans[j->id] = T.get_sum(R[map[j->x]->id]) - T.get_sum(L[map[j->x]->id] - 1);
		else if (s[i] == 'B') {
			if (t->fa) {
				T.update(L[t->id], -1);
				t = t->fa;
			}
		}
		else {
			t = t->ch[idx(s[i])];
			T.update(L[t->id], 1);
		}
	}
	for (int i = 0; i < m; ++i)
		printf("%d\n", ans[i]);
}
