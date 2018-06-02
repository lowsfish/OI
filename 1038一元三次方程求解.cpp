#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
double a,b,c,d;
inline double f(double x)
{
	return a*x*x*x+b*x*x+c*x+d;
}
int main()
{
//	freopen("1.in","r",stdin);
	int sum=0;
	cin>>a>>b>>c>>d;
	double t1,t2;
	/*while(ans<=100)
	{
		double t=ans-0.01;
		double n=a*ans*ans*ans+b*ans*ans+c*ans+d;
		double m=a*t*t*t+b*t*t+c*t+d;
		if(n*m<=0 && sum<3) {
			printf("%.2f ",t);
			++sum;
		}
		ans+=0.005;
	}*/
	for(double i=-100;i<=100;i+=0.005)
	{
		if(f(i)*f(i+0.005)<0) printf("%.2lf ",i);		
	}
	cout<<endl;
	return 0;
}
