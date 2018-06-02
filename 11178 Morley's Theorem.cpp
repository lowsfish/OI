#include<cstdio>
#include<cmath>
struct Point{
	double x,y;
	Point(double x=0,double y=0):x(x),y(y) {}
};
typedef Point Vector;
inline Point read_point()
{
	double x,y;
	scanf("%lf%lf",&x,&y);
	return Point(x,y);
}
Vector operator-(Point A,Point B)
{
	return Vector(A.x-B.x,A.y-B.y);
}
Vector operator*(Vector A,double p)
{
	return Vector(A.x*p,A.y*p);
}
Vector operator+(Vector A,Vector B)
{
	return Vector(A.x+B.x,A.y+B.y);
}
inline Vector Rotate(Vector A,double rad)
{
	return Vector(A.x*cos(rad)-A.y*sin(rad),A.x*sin(rad)+A.y*cos(rad));
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
inline double Dot(Vector A,Vector B)
{
	return A.x*B.x+A.y*B.y;
}
inline double Length(Vector A)
{
	return sqrt(Dot(A,A));
}
inline double Angle(Vector A,Vector B)
{
	return acos(Dot(A,B)/Length(A)/Length(B));
}
Point GetD(Point A,Point B,Point C)
{
	double r1=Angle(A-B,C-B),r2=Angle(B-C,A-C);
	Vector v=Rotate(C-B,r1/3),w=Rotate(B-C,-r2/3);
	return GetLineIntersection(B,v,C,w);
}
int T;
int main()
{
	//freopen("1.in","r",stdin);
	Point A,B,C,D,E,F;
	scanf("%d",&T);
	while(T--)
	{
		A=read_point();
		B=read_point();
		C=read_point();
		D=GetD(A,B,C);
		E=GetD(B,C,A);
		F=GetD(C,A,B);
		printf("%6f %6f %6f %6f %6f %6f\n",D.x,D.y,E.x,E.y,F.x,F.y);
	}
	return 0;
}
