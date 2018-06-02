#include<iostream>
#include<cstdio>
#include<cstring>
#define MAXSZ 110
using namespace std;
int a[MAXSZ];
int main()
{
    int n,ans=0,i,avl=0;
    cin>>n;
    for(i=0;i<n;++i)
    {
                    cin>>a[i];
                    avl+=a[i];
                    }
    avl/=n;
    for(i=0;i<n;++i) a[i]-=avl;
    for(i=1;i<n;++i)
    {
           if(a[i-1]!=0)
           {
                       ++ans;
                       a[i]+=a[i-1];
                       a[i-1]=0;
                       }         
                    }
    cout<<ans<<endl;
    return 0;
    
    }
