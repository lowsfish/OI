#include<iostream>
#include<cstdlib>
#include<ctime>
#define MAXSZ 110
using namespace std;
int mat[MAXSZ][MAXSZ];
int V;
int main()
{
    freopen("1.in","r",stdin);
    freopen("1.out","w",stdout);
    ios::sync_with_stdio(false);
    cin>>V;
    for(int i=0;i<V;++i)
       for(int j=0;j<V;++j)
       {
               cin>>mat[i][j];
               }
    for(int k=0;k<V;++k)
       for(int i=0;i<V;++i)
          for(int j=0;j<V;++j)
          mat[i][j]=min(mat[i][j],mat[i][k] + mat[k][j]);
    int n;
    cin>>n;
    for(int i=0;i<n;++i)
    {
            int s,t;
            cin>>s>>t;
            --s;--t;
            cout<<mat[s][t]<<endl;
            }
    return 0;
}
