#include<cstdio>
#include<cmath>
double a;
inline double f(double x)
{
	return sqrt(1+4*a*a*x*x);
}
inline double simpson(double a,double b)
{
	double c=a+(b-a)/2;
	return (f(a)+4*f(c)+f(b))*(b-a)/6;
}
double asr(double a,double b,double eps,double A)
{
	double c=a+(b-a)/2;
	double L=simpson(a,c),R=simpson(c,b);
	if(fabs(L+R-A)<=15*eps) return L+R+(L+R-A)/15.0;
	else return asr(a,c,eps/2,L)+asr(c,b,eps/2,R);
}
int T;
int D,H,B,L;
int main()
{
//	freopen("1.in","r",stdin);
	scanf("%d",&T);
	for(int kase=1;kase<=T;++kase)
	{
		scanf("%d%d%d%d",&D,&H,&B,&L);
		int n=(B+D-1)/D;
		double D1=(double)B/n,L1=(double)L/n;
		double x=0,y=H;
		while(y-x>1e-7)
		{
			double m=x+(y-x)/2;
			a=4*m/(D1*D1);
			if(asr(0,D1/2,1e-6,simpson(0,D1/2))*2<L1) x=m;
			else y=m;
		}
		if(kase>1) putchar(10);
		printf("Case %d:\n%.2f\n",kase,H-x);
	}
	return 0;
}
