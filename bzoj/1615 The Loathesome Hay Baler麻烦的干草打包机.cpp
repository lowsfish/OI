#include<cstdio>
#include<queue>
#include<cmath>
const int MAXN=1050+5;
const double eps=1e-12;
struct Circle{
	double x,y,r;
	Circle(double x=0,double y=0,double r=0):x(x),y(y),r(r) {}
}c[MAXN];
bool used[MAXN];
inline double sqr(double x)
{
	return x*x;
}
inline double dist(double x1,double y1,double x2,double y2)
{
	return sqrt(sqr(x1-x2)+sqr(y1-y2));
}
inline bool tangency(Circle c1,Circle c2)
{
	return fabs(dist(c1.x,c1.y,c2.x,c2.y)-c1.r-c2.r)<=eps;
}
inline bool cmp(double x1,double y1,double x2,double y2)
{
	return fabs(x1-x2)<=eps && fabs(y1-y2)<=eps;
}
int n;
double xt,yt;
int st,en;
struct Node{
	int pos;
	double v,sum;
	Node(int pos,double v,double sum):pos(pos),v(v),sum(sum) {}
};
int bfs()
{
	std::queue<Node> que;
	que.push(Node(st,10000,10000));
	while(!que.empty())
	{
		Node x=que.front();que.pop();
		for(int i=0;i<n;++i) if(tangency(c[x.pos],c[i]) && !used[i])
		{
			used[i]=1;
			double v=c[x.pos].r/c[i].r*x.v;
			if(i==en) return (int)(x.sum+v);
			que.push(Node(i,v,x.sum+v));
		}
	}
}
int main()
{
	//freopen("1.in","r",stdin);
	scanf("%d%lf%lf",&n,&xt,&yt);
	for(int i=0;i<n;++i)
	{
		scanf("%lf%lf%lf",&c[i].x,&c[i].y,&c[i].r);
		if(cmp(c[i].x,c[i].y,0,0)) st=i,used[i]=1;
		if(cmp(c[i].x,c[i].y,xt,yt)) en=i;
	}
	printf("%d\n",bfs());
	return 0;
}
