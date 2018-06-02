#include <cstdio>
#include <vector>
#include <algorithm>
typedef long long LL;
const int MAX_N = 1 << 10;
LL gcd(LL a, LL b) {
	return b ? gcd(b, a % b) : a;
}
std::vector<int> a;
int l, r;
void pre_do(LL x) {
	if (x > r) return;
	if (x) a.push_back(x);
	pre_do(x * 10 + 2);
	pre_do(x * 10 + 9);
}
LL ans = 0;
void dfs(int cur, int f, LL num) {
	if (num > r) return;
	if (cur == a.size()) {
		if (f & 1) ans += r / num - (l - 1) / num;
		else if (f) ans -= r / num - (l - 1) / num;
		return;
	}
	dfs (cur + 1, f, num);
	dfs (cur + 1, f + 1, num * a[cur] / gcd(num, a[cur]));
}
int main() {
	scanf("%d%d", &l, &r);
	pre_do(0);
	std::sort(a.begin(), a.end());
	for (int i = 0; i < a.size(); ++i) {
		std::vector<int>::iterator j = a.begin() + i + 1;
		while (j != a.end()) {
			if (*j % a[i] == 0) a.erase(j);
			else ++j;
		}
	}
	dfs(0, 0, 1);
	printf("%lld\n", ans);
}
