#include <cstdio>
#include <vector>
#include <cstring>
using std::vector;
const int MAX_V = 10000 + 5;
const int MAX_N = 1000000 + 5;
vector<int> G[MAX_V];
int state[MAX_N], lnk[MAX_N];
bool find(int x) {
	for (vector<int>::iterator i = G[x].begin(); i != G[x].end(); ++i)
		if (state[*i] != x) {
			state[*i] = x;
			if (lnk[*i] == -1 || find(lnk[*i])) {
				lnk[*i] = x;
				return true;
			}
		}
	return false;
}
int main() {
	memset(lnk, -1, sizeof lnk);
	int n;
	scanf("%d", &n);
	for (int i = 0; i < n; ++i) {
		int a, b;
		scanf("%d%d", &a, &b);
		G[a].push_back(i);
		G[b].push_back(i);
	}
	for (int i = 1; ; ++i) if (!find(i)) {
		printf("%d\n", i - 1);
		return 0;
	}
}
