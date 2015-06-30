#include <cstdio>
#include <cmath>
#include <algorithm>
const int MAX_N = 500 + 5;
const double eps = 1e-15;
const int INF = ~0U >> 2;
int m, n;
int mat[MAX_N][MAX_N];
inline int dcmp(double x) {
	if (fabs(x) <= eps) return 0;
	return x < 0 ? -1 : 1;
}
struct Point {
	double x, y;
	Point() {}
	Point(double x, double y):x(x), y(y) {}
};
typedef Point Vector;
bool operator==(Point A, Point B) {
	return dcmp(A.x - B.x) == 0 && dcmp(A.y - B.y) == 0;
}
bool operator!=(Point A, Point B) {
	return !(A == B);
}
Vector operator+(Vector A, Vector B) {
	return Vector(A.x + B.x, A.y + B.y);
}
Vector operator-(Vector A, Vector B) {
	return Vector(A.x - B.x, A.y - B.y);
}
Point p1[MAX_N], p2[MAX_N];
inline double Cross(Vector A, Vector B) {
	return A.x * B.y - B.x * A.y;
}
inline double Dot(Vector A, Vector B) {
	return A.x * B.x + A.y * B.y;
}
inline bool on_segment(Point A, Point B, Point C) { //[A,B]
	return !dcmp(Cross(A - B, C - A)) && dcmp(Dot(C - A, C - B)) <= 0;
}
bool judge(int i, int j) {
	Vector u = p1[j] - p1[i];
	for (int k = 0; k < n; ++k)
		if (dcmp(Cross(u, p2[k] - p1[i])) != 1 && !on_segment(p1[i], p1[j], p2[k]))
			return false;
	return true;
}
int main() {
	scanf("%d%d", &m ,&n);
	double t;
	for (int i = 0; i < m; ++i) scanf("%lf%lf%lf", &p1[i].x, &p1[i].y, &t);
	for (int i = 0; i < n; ++i) scanf("%lf%lf%lf", &p2[i].x, &p2[i].y, &t);
	if (m == 1) {
		for (int i = 0; i < n; ++i)
			if(p2[i] != p1[0]) {
				puts("-1");
				return 0;
			}
		puts("1");
		return 0;
	}
	for (int i = 0; i < m; ++i)
		for (int j = 0; j < m; ++j)
			mat[i][j] = INF;
	for (int i = 0; i < m; ++i)
		for (int j = 0; j < m; ++j)
			if (i != j && judge(i, j))
				mat[i][j] = 1;
	for (int k = 0; k < m; ++k)
		for (int i = 0; i < m; ++i)
			for (int j = 0; j < m; ++j)
				mat[i][j] = std::min(mat[i][j], mat[i][k] + mat[k][j]);
	int ans = INF;
	for (int i = 0; i < m; ++i) ans = std::min(ans, mat[i][i]);
	if(ans == INF) ans = -1;
	printf("%d\n", ans);
}
