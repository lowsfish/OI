#include<cstdio>
#include<set>
#include<cmath>
const double eps=1e-12;
const double INF=1e20;
const int MAXN=200+5;
struct cmp{
	bool operator()(const double&a,const double& b)
	{
		if(fabs(a-b)<=eps) return 0;
		return a<b;
	}
};
std::set<double,cmp> st;
double x[MAXN],y[MAXN];
inline double slope(double x1,double y1,double x2,double y2)
{
	if(fabs(x1-x2)<=eps) return INF;
	return (y1-y2)/(x1-x2);
}
int main()
{
	freopen("1.in","r",stdin);
	int n;
	scanf("%d",&n);
	for(int i=0;i<n;++i)
		scanf("%lf%lf",x+i,y+i);
	int ans=0;
	for(int i=0;i<n;++i)
		for(int j=i+1;j<n;++j)
		{
			double d=slope(x[i],y[i],x[j],y[j]);
			if(st.find(d)==st.end()) ++ans,st.insert(d);
		}
	printf("%d\n",ans);
	return 0;
}
