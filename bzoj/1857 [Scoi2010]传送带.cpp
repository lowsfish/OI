#include<cstdio>
#include<algorithm>
#include<cmath>
#define x first
#define y second
const double eps=1e-4;
typedef std::pair<double,double> Point;
inline double sqr(const double& x)
{
	return x*x;
}
inline double dist(const Point& a,const Point& b)
{
	return sqrt(sqr(a.x-b.x)+sqr(a.y-b.y));
}
Point A,B,C,D;
int p,q,r;
double calc(Point a)
{
	double lx=C.x,ly=C.y,rx=D.x,ry=D.y;
	while(fabs(rx-lx)>eps || fabs(ry-ly)>eps)
	{
		double x1=lx+(rx-lx)/3,y1=ly+(ry-ly)/3;
		double x2=rx-(rx-lx)/3,y2=ry-(ry-ly)/3;
		double t1=dist(a,A)/p+dist(Point(x1,y1),D)/q+dist(Point(x1,y1),a)/r;
		double t2=dist(a,A)/p+dist(Point(x2,y2),D)/q+dist(Point(x2,y2),a)/r;
		if(t1<t2) rx=x2,ry=y2;
		else lx=x1,ly=y1;
	}
	return dist(A,a)/p+dist(Point(lx,ly),D)/q+dist(Point(lx,ly),a)/r;
}
int main()
{
	scanf("%lf%lf%lf%lf%lf%lf%lf%lf%d%d%d",&A.x,&A.y,&B.x,&B.y,&C.x,&C.y,&D.x,&D.y,&p,&q,&r);
	double lx=A.x,ly=A.y,rx=B.x,ry=B.y;
	while(fabs(rx-lx)>eps || fabs(ry-ly)>eps)
	{
		double x1=lx+(rx-lx)/3,y1=ly+(ry-ly)/3;
		double x2=rx-(rx-lx)/3,y2=ry-(ry-ly)/3;
		double t1=calc(Point(x1,y1)),t2=calc(Point(x2,y2));
		if(t1<t2) rx=x2,ry=y2;
		else lx=x1,ly=y1;
	}
	printf("%.2f\n",calc(Point(lx,ly)));
	return 0;
}
