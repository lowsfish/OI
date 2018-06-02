#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#define MAX 105
using namespace std;
char mat[MAX][MAX];
int fa[MAX][MAX],ans;
int dx[]={-1,-1,-1,0,0,1,1,1},dy[]={-1,0,1,-1,1,-1,0,1};
typedef pair<int,int> P;
queue<P> que;
int x,y,mx,my;
bool judge()
{
     ans=0;
     for(int i=1;i<=y;++i)
     for(int j=1;j<=x;++j)
             {
                          if(mat[i][j]=='.') return 0;
                          ans=max(ans,fa[i][j]);
             }
     return 1;
     }
     
void print()
{
     for(int i=1;i<=y;++i)
     {for(int j=1;j<=x;++j)
     cout<<mat[i][j];
     cout<<endl;}
     }
int main()
{
    cin>>x>>y>>mx>>my;
    cin.get();
    for(int i=y;i>=1;--i)
            cin.getline(mat[i]+1,MAX);
    mat[my][mx]='M';
    que.push(P(my,mx));
    
    while(!que.empty())
         {
		 P p=que.front();que.pop();

         for(int i=0;i<8;++i)
         {
                 int ny=p.first+dy[i],nx=p.second+dx[i];
                 if(nx>=1 && nx<=x && ny>=1 && ny<=y && mat[ny][nx]=='.')
                 {
                          mat[ny][nx]='M';
                          que.push(P(ny,nx));
                          fa[ny][nx]=fa[p.first][p.second]+1;
                 }    
         }   

         if(judge())
         {
                    cout<<ans;
                    return 0;
         }               
                       
    }
    return 0;
    
    }

