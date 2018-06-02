#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#include <iostream>
const int MAX_N = 20000 + 5;
int pa[MAX_N], d[MAX_N];
int n, nQ;
void init() {
	for (int i = 0; i <= n; ++i)
		pa[i] = i;
	memset(d, 0, sizeof d);
}
int find(int x) {
	if (pa[x] != x) {
		int root = find(pa[x]);
		d[x] ^= d[pa[x]];
		return pa[x] = root;
	}
	else return x;
}
bool unite(int x, int y, int c) {
	int rx = find(x), ry = find(y);
	if (rx == ry) {
		if ((d[x] ^ d[y]) != c) return false;
		else return true;
	}
	if (rx == n) std::swap(rx, ry);
	pa[rx] = ry;
	d[rx] = d[x] ^ d[y] ^ c;
	return true;
}
bool vis[MAX_N];
int k, a[MAX_N], ans;
bool query() {
	memset(vis, false, sizeof vis);
	ans = 0;
	for (int i = 0; i < k; ++i) {
		if (vis[i]) continue;
		int root = find(a[i]);
		bool num = 0;
		for (int j = i; j < k; ++j)
			if (!vis[j] && find(a[j]) == root) {
				num ^= 1;
				vis[j] = true;
				ans ^= d[a[j]];
			}
		if (root != n && num) return false;
	}
	return true;
}
int p, q, v;
void get(char* s) {
	p = q = v = -1;
	int num = 0;
	while (*s) {
		if (*s == ' ') ++num, ++s;
		else {
			int x = 0;
			while (isdigit(*s))
				x = x * 10 + (*s++) - '0';
			if (p == -1) p = x;
			else if (q == -1) q = x;
			else v = x;
		}
	}
	if (num == 2) v = q, q = n;
}
int main() {
	//freopen("1.in", "r", stdin);
	int kase = 0;
	while (scanf("%d%d", &n, &nQ) == 2 && n) {
		printf("Case %d:\n", ++kase);
		bool flag = false;
		init();
		char cmd[2];
		int t = 0;
		while (nQ--) {
			scanf("%s", cmd);
			if (cmd[0] == 'I') {
				++t;
				char s[100];
				//fgets(s, 100, stdin);
				std::cin.getline(s, 100);
				if (flag) continue;
				get(s);
				if (!unite(p, q, v)) {
					printf("The first %d facts are conflicting.\n", t);
					flag = true;
				}
			}
			else {
				scanf("%d", &k);
				for (int i = 0; i < k; ++i)
					scanf("%d", a + i);
				if (flag) continue;
				if (!query()) puts("I don't know.");
				else printf("%d\n", ans);
			}
		}
		puts("");
	}
}
