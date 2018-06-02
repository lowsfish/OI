#include <cstdio>
#include <algorithm>
#include <ext/pb_ds/priority_queue.hpp>
typedef __gnu_pbds::priority_queue<int> PQ;
const int MAX_N = 1000000 + 5;
PQ root[MAX_N];
#define BUFSIZE 1000000
char buf[BUFSIZE], *pt = buf + BUFSIZE, *pend = buf + BUFSIZE;
int sign;
#define read() \
	do{ \
		if (pt >= pend) \
		{ \
			pt = buf; \
			fread(buf, 1, BUFSIZE, stdin); \
		} \
	} while(0)

#define scan(t) \
{ \
	t = 0;sign=1; \
	read(); \
	while ((*pt<'0'||*pt>'9')&&*pt!='-') {pt ++; read();} \
	if(*pt=='-')sign=-1,pt++;\
	while (((*pt) >= '0' && (*pt) <= '9')) {t = t * 10 + (*(pt ++)) - '0'; read();}\
	t*=sign;\
}
int a[MAX_N];
int l[MAX_N], r[MAX_N];
int n;
int main() {
	scan(n);
	for (int i = 0; i < n; ++i) {
		scan(a[i]);
		a[i] -= i;
	}
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
	long long ans = 0;
	for (int i = 0; i < cnt; ++i) {
		int t = root[i].top();
		for (int j = l[i]; j <= r[i]; ++j)
			ans += std::abs(t - a[j]);
	}
	printf("%lld\n", ans);
}
