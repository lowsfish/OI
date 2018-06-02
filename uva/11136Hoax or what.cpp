#include <bits/stdc++.h>
using std::multiset;
multiset<int> s;
int n;
int main() {
	while (scanf("%d", &n) != EOF && n) {
		s.clear();
		long long ans = 0;
		for (int i = 0; i < n; ++i) {
			int t;
			scanf("%d", &t);
			for (int j = 0; j < t; ++j) {
				int t2;
				scanf("%d", &t2);
				s.insert(t2);
			}
			int mx = *s.rbegin(), mn = *s.begin();
			ans += mx - mn;
			s.erase(s.begin());
			s.erase(--s.end());
		}
		std::cout << ans << std::endl;
	}
}
