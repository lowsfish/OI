/*
ID: rainbow16
LANG: C++
TASK: fracdec
*/
/*
对于一个最简分数n/d,d=(2^x)*(5^y)*m,m!=1,那么其循环节长度为使10^L mod m==1的最小的L,不循环长度为max(x,y)
*/
#include<iostream>
#include<sstream>
#include<cstdio>
#include<iomanip>
#include<algorithm>
#include<string>
using namespace std;
typedef long long LL;
string s;
int pow_mod(int a,int b,int mod)
{
	LL base=a,ans=1;
	while(b)
	{
		if(b&1) ans=ans*base%mod;
		base=base*base%mod;
		b>>=1;
	}
	return (int)ans;
}
int gcd(int a,int b)
{
	return b==0?a:gcd(b,a%b);
}
int x,y,m,n,d;	// n/d d=2^x * 5^y * m
int main()
{
	freopen("fracdec.in","r",stdin);
	freopen("fracdec.out","w",stdout);
	stringstream ss;
	cin>>n>>d;
	int g=gcd(n,d);
	n/=g;d/=g;
	m=d;
	while(m>1 && (m&1)==0) m>>=1,++x;
	while(m>1 && (m%5)==0) m/=5,++y;
	if(m==1) 
	{
		if(n%d==0) ss<<n/d<<".0";
		else ss<<setprecision(max(x,y))<<setiosflags(ios::fixed)<<(double)n/(double)d;
	}
	else
	{
		int i;
		for(i=1;;++i) if(pow_mod(10,i,m)==1) break;
		//printf("%d\n",i);
		ss<<n/d<<'.';
		n%=d;
		for(int j=0;j<max(x,y)+i;++j)
		{
			if(j==max(x,y)) ss<<'(';
			n*=10;
			ss<<n/d;
			n%=d;
		}
		ss<<')';
	}
	ss>>s;
	int sz=s.length();
	for(int i=0;i<sz;++i)
	{
		if(i%76==0 && i!=0) putchar(10);
		putchar(s[i]);
	}
	putchar(10);
	return 0;
}
