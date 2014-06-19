#include<iostream>
#include<cstdio>
#include<cstdlib>
#define MX 5000
using namespace std;
int main()
{

    int a[MX][3],i=0,j,n,m=0,M=0;
    cin>>n;

    for(i=0;i<n;++i) {cin>>a[i][0];a[i][1]=1;a[i][2]=0;}
    for (i=n-2;i>=0;--i)
       for (j=i+1;j<n;++j)
       {
           if (a[j][0]>a[i][0]&&a[j][1]>=a[i][1])
              {a[i][1]=a[j][1]+1;a[i][2]=j;}
           }
    for(i=0;i<n;++i) if(a[i][1]>M){M=a[i][1];m=i;}
    cout<<"max="<<M<<endl;
    cout<<a[m][0]<<' ';
    m=a[m][2];
    while(m) {cout<<a[m][0]<<' ';if(m==0)break;m=a[m][2];}
       return 0;
    }
