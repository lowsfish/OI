#include<cstdio>
#include<algorithm>
#include<cmath>
const int MAXN=10+5;
const double eps=1e-10;
typedef double Matrix[MAXN][MAXN];
double po[MAXN][MAXN];
inline double sqr(double x)
{
	return x*x;
}
void gauss(Matrix A,int n)
{
	for(int i=0;i<n;++i)
	{
		int r=i;
		for(int j=i+1;j<n;++j) if(fabs(A[j][i])>fabs(A[r][i])) r=j;
		if(r!=i) std::swap(A[r],A[i]);
		for(int j=i+1;j<n;++j)
		{
			double f=A[j][i]/A[i][i];
			for(int k=i;k<=n;++k) A[j][k]-=f*A[i][k];
		}
	}
	for(int i=n-1;i>=0;--i)
	{
		A[i][n]/=A[i][i];
		for(int j=i-1;j>=0;--j) A[j][n]-=A[i][n]*A[j][i];
	}
}
Matrix A;
int n;
int main()
{
	scanf("%d",&n);
	for(int i=0;i<=n;++i)
		for(int j=0;j<n;++j) scanf("%lf",&po[i][j]);
	double tmp=0;
	for(int i=0;i<n;++i) tmp+=sqr(po[0][i]);
	for(int i=0;i<n;++i)
	{
		A[i][n]=tmp;
		for(int j=0;j<n;++j)
		{
			A[i][n]-=sqr(po[i+1][j]);
			A[i][j]=2*(po[0][j]-po[i+1][j]);
		}
	}
	gauss(A,n);
	for(int i=0;i<n;++i)
		printf("%.3f%c",A[i][n]+eps,i==n-1?'\n':' ');
	return 0;
}
