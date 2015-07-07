#include <cstdio>
#include <cstring>
#include <algorithm>
const int MAXN = 1000000 + 5;
char s1[MAXN], s2[MAXN];
typedef std::pair<int, int> PII;
inline int idx(char c) {
	return c - 'A';
}
PII a[MAXN], b[MAXN];
int n;
int fl[MAXN];
int bit[MAXN];
inline int lowbit(int x) {
	return x & -x;
}
void update(int x, int add) {
	for (; x <= n; x += lowbit(x))
		bit[x] += add;
}
int get_sum(int x) {
	int ans = 0;
	for (; x > 0; x -= lowbit(x))
		ans += bit[x];
	return ans;
}
int main() {
	scanf("%d%s%s", &n, s1, s2);
	for (int i = 0; i < n; ++i)
		a[i] = PII(idx(s1[i]), i + 1), b[i] = PII(idx(s2[i]), i + 1);
	std::stable_sort(a, a + n);
	std::stable_sort(b, b + n);
	for (int i = 0; i < n; ++i) fl[a[i].second] = b[i].second;
	long long ago = 0;
	for (int i = 1; i <= n; ++i) {
		update(fl[i], 1);
		ago += i - get_sum(fl[i]);
	}
	printf("%lld\n", ago);
}
