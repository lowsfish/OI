#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cstdlib>
const int MAXN = 10000 + 5;
const int MAXT = 50000 + 5;
using std::swap;
using std::min;
using std::max;
int n, m;
int w[MAXN], b[MAXN];
double ans = 0.0;
int a1[MAXN >> 1], a2[MAXN >> 1];
void climb_mountains() {
	int sumw1 = 0, sumb1 = 0, sumw2 = 0, sumb2 = 0;
	for (int i = 0; i < n; ++i) {
		if(i & 1) a1[i >> 1] = i, sumw1 += w[i], sumb1 += b[i];
		else a2[i >> 1] = i, sumw2 += w[i], sumb2 += b[i];
	}
	double tans = min((double)sumw1 / (sumw1 + sumb1), (double)sumw2 / (sumw2 + sumb2));
	for (int T = 0; T < MAXT; ++T) {
		int t1 = rand() % (n >> 1), t2 = rand() % (n >> 1);
		int tsumw1 = sumw1 + w[a2[t2]] - w[a1[t1]], tsumb1 = sumb1 + b[a2[t2]] - b[a1[t1]];
		int tsumw2 = sumw2 - (w[a2[t2]] - w[a1[t1]]), tsumb2 = sumb2 - (b[a2[t2]] - b[a1[t1]]);
		double t = min((double)tsumw1 / (tsumw1 + tsumb1), (double)tsumw2 / (tsumw2 + tsumb2));
		if (t > tans) {
			tans = t;
			sumw1 = tsumw1;
			sumb1 = tsumb1;
			sumw2 = tsumw2;
			sumb2 = tsumb2;
			swap(a1[t1], a2[t2]);
		}
	}
	if(tans > 0.5) ans = std::max(ans, tans);
}
int main() {
	srand(233333);
	while(scanf("%d%d", &n, &m) != EOF) {
		ans = 0.0;
		int sumw = 0, sumb = 0;
		for (int i = 0; i < n; ++i) {
			scanf("%d%d", w + i, b + i);
			sumw += w[i];
			sumb += b[i];
		}
		if (sumw == sumb) {
			puts("No solution");
			continue;
		}
		bool flag = 0;
		if (sumw < sumb) swap(w, b), swap(sumw, sumb), flag = 1;
		for(int i = 0; i < 5; ++i) climb_mountains();
		if(ans == 0.0) puts("No solution");
		else printf("%c %.2f\n",flag ? 'B' : 'W', ans * 100.0);
	}
	return 0;
}
