#include<cstdio>
#include<cmath>
#include<iostream>
using namespace std;
const double eps=1e-10;
struct Point{
	double x,y;
	Point(double x=0,double y=0):x(x),y(y) {}
};
typedef Point Vector;
istream& operator>>(istream& in,Point &A)
{
	in>>A.x>>A.y;
	return in;
}
Vector operator-(Point A,Point B)
{
	return Vector(A.x-B.x,A.y-B.y);
}
Vector operator*(Vector A,double p)
{
	return Vector(A.x*p,A.y*p);
}
Point operator+(Point A,Vector B)
{
	return Point(A.x+B.x,A.y+B.y);
}
inline double cross(Vector A,Vector B)
{
	return A.x*B.y-B.x*A.y;
}
inline Point GetLineIntersection(Point P,Vector v,Point Q,Vector w)
{
	Vector u=P-Q;
	double t=cross(w,u)/cross(v,w);
	return P+v*t;
}
int n;
int main()
{
	//freopen("1.in","r",stdin);
	scanf("%d",&n);
	printf("INTERSECTING LINES OUTPUT\n");
	while(n--)
	{
		Point p1,p2,p3,p4;
		Vector v,w;
		cin>>p1>>p2>>p3>>p4;
		v=p2-p1;w=p4-p3;
		if(fabs(cross(v,w))<=eps)
		{
			Vector u=p3-p2;
			if(fabs(cross(u,v))<=eps) printf("LINE\n");
			else printf("NONE\n");
		}
		else
		{
			Point p=GetLineIntersection(p1,v,p3,w);
			printf("POINT %.2f %.2f\n",p.x,p.y);
		}
	}
	printf("END OF OUTPUT\n");
	return 0;
}
