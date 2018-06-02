#include<cstdio>
#include<cmath>
const double eps=1e-14;
int p,q,r,s,t,u;
inline double f(double x)
{
	return p*exp(-x)+q*sin(x)+r*cos(x)+s*tan(x)+t*x*x+u;
}
int main()
{
//	freopen("1.in","r",stdin);
	while(scanf("%d%d%d%d%d%d",&p,&q,&r,&s,&t,&u)!=EOF)
	{
		if(f(0)<-eps || f(1)>eps) printf("No solution\n");
		else
		{
			double L=0,R=1,M;
			while(R-L>1e-10)
			{
				M=L+(R-L)/2;
				if(f(M)>0) L=M;
				else R=M;
			}
			printf("%.4f\n",M);
		}
	}
	return 0;
}
