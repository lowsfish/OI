#include<iostream>
#include<cstdio>
using namespace std;
typedef unsigned long long l;
l f(l a,l b,l m)
{
    l res=1,t=a%m;
    while(b)
    {
            if(b&1) res=res*t%m;
            t=t*t%m;
            b>>=1;
            }
    return res;
}
int main()
{
    l a,b,m;
    cin>>a>>b>>m;
    cout<<f(a,b,m);
    cin.get();
    cin.get();
    return 0;
}
              
