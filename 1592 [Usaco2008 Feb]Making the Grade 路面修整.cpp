#include <cstdio>
#include <algorithm>
#include <ext/pb_ds/priority_queue.hpp>
typedef __gnu_pbds::priority_queue<int> PQ;
const int MAX_N = 2000 + 5;
PQ root[MAX_N];
int a[MAX_N];
int l[MAX_N], r[MAX_N];
int n;
int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; ++i)
		scanf("%d", a + i);
	int cnt = 0;
	for (int i = 0; i < n; ++i) {
		root[cnt].clear();
		root[cnt].push(a[i]);
		l[cnt] = r[cnt] = i;
		while (cnt > 0 && root[cnt].top() < root[cnt - 1].top()) {
			--cnt;
			root[cnt].join(root[cnt + 1]);
			r[cnt] = r[cnt + 1];
			while(root[cnt].size() * 2 > r[cnt] - l[cnt] + 2)
				root[cnt].pop();
		}
		++cnt;
	}
	int ans = 0;
	for (int i = 0; i < cnt; ++i) {
		int t = root[i].top();
		for (int j = l[i]; j <= r[i]; ++j)
			ans += std::abs(t - a[j]);
	}
	printf("%d\n", ans);
}
