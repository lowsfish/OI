#include<cstdio>
#include<algorithm>
#include<cmath>
#include<vector>
const double eps=1e-10;
const int MAXN=50000+5;
struct Line{
	double A,B;
	int id;
	bool operator<(const Line& l)const
	{
		if(fabs(A-l.A)<=eps) return B<l.B;
		return A<l.A;
	}
};
bool ans[MAXN];
Line line[MAXN];
Line stk[MAXN];
int top;
inline double crossx(Line a,Line b)
{
	return (a.B-b.B)/(b.A-a.A);
}
inline void insert(Line a)
{
	while(top)
	{
		if(fabs(stk[top-1].A-a.A)<=eps) --top;
		else if(top>1 && crossx(a,stk[top-2])<=crossx(stk[top-1],stk[top-2]))
			--top;
		else break;
	}
	stk[top++]=a;
}
int main()
{
	int n;
	scanf("%d",&n);
	for(int i=0;i<n;++i)
		line[i].id=i+1,scanf("%lf%lf",&line[i].A,&line[i].B);
	std::sort(line,line+n);
	for(int i=0;i<n;++i) insert(line[i]);
	for(int i=0;i<top;++i) ans[stk[i].id]=1;
	for(int i=1;i<=n;++i) if(ans[i]) printf("%d ",i);
	puts("");
	return 0;
}
