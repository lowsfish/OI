#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
using namespace std;
const double g=10;
double H,S1,V,L,K;
int n;
int main()
{
	cin>>H>>S1>>V>>L>>K>>n;
	double t1=sqrt(2*(H-K)/g),t2=sqrt(2*H/g);
	double S2=S1-t1*V+L,S3=S1-t2*V;
	if(S2<0 || S3>n)
	{
		printf("0\n");
		return 0;
	}
	if(abs((int)(S2+0.5)-S2)<=1e-5) S2+=0.5;
	if(abs((int)(S3+0.5)-S3)<=1e-5) S3+=0.5;
	if(S3<0) S3=0;
	if(S2>n) S2=n;
	printf("%d\n",(int)(S2)-(int)S3);
	return 0;
}
