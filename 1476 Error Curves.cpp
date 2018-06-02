#include<cstdio>
#include<algorithm>
const int MAXN=10000+5;
int n;
int a[MAXN],b[MAXN],c[MAXN];
inline double f(int i,double x)
{
	return a[i]*x*x+b[i]*x+c[i];
}
inline double F(double x)
{
	double ans=f(0,x);
	for(int i=1;i<n;++i)
		ans=std::max(ans,f(i,x));
	return ans;
}
int T;
int main()
{
//	freopen("1.in","r",stdin);
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&n);
		for(int i=0;i<n;++i) scanf("%d%d%d",a+i,b+i,c+i);
		double L=0.0,R=1000.0;
		while(R-L>1e-9)
		{
			double M1=L+(R-L)/3,M2=R-(R-L)/3;
			if(F(M1)>F(M2)) L=M1;
			else R=M2;
		}
		printf("%.4f\n",F(L));
	}
	return 0;
}
