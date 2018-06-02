#include<cstdio>
#include<cmath>
#include<cstdlib>
#include<ctime>
const double eps=1e-2;
const int MAXN=100+5;
int n;
struct Point{
	double x,y;
	Point(double x=0,double y=0):x(x),y(y) {}
}p[MAXN];
inline double dist(Point a,Point b)
{
	double dx=a.x-b.x,dy=a.y-b.y;
	return sqrt(dx*dx+dy*dy);
}
inline double totdist(Point a)
{
	double ans=0;
	for(int i=0;i<n;++i)
		ans+=dist(a,p[i]);
	return ans;
}
Point po;
int dx[]={0,1,0,-1},dy[]={1,0,-1,0};
int main()
{
	//freopen("1.in","r",stdin);
	srand(233333);
	scanf("%d",&n);
	for(int i=0;i<n;++i)
		scanf("%lf%lf",&p[i].x,&p[i].y);
	po=p[0];
	double sum=(totdist(po));
	double t=10000;
	while(t>eps)
	{
		for(int i=0;i<4;++i)
		{
			Point np=Point(po.x+dx[i]*t,po.y+dy[i]*t);
			double nsum=totdist(np);
			if(nsum<sum) sum=nsum,po=np;
			//else if(log((nsum-sum)/t)<(rand()%10000)/10000.0);
			//	sum=nsum,po=np;
		}
		t*=0.8;
	}
	printf("%.0f\n",sum);
	return 0;
}
