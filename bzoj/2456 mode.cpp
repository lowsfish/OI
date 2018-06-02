#include <cstdio>
int n, t1 = -1, t2, cnt;
int main() {
	scanf("%d", &n);
	while(n--) {
		scanf("%d", &t2);
		if(t2 == t1) ++cnt;
		else if(cnt == 0) t1 = t2, cnt = 1;
		else --cnt;
	}
	printf("%d\n", t1);
}
