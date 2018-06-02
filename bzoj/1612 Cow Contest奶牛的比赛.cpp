#include<cstdio>
const int MAXN=100+5;
bool mat[MAXN][MAXN];
int win[MAXN],lose[MAXN];
int n,m;
int main()
{
    scanf("%d%d",&n,&m);
    while(m--)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        mat[x][y]=1;    
    }
    for(int k=1;k<=n;++k)
        for(int i=1;i<=n;++i)
            for(int j=1;j<=n;++j)
                mat[i][j]|=mat[i][k]&&mat[k][j];
    for(int i=1;i<=n;++i)
        for(int j=1;j<=n;++j)
            win[i]+=mat[i][j],lose[j]+=mat[i][j];
    int ans=0;
    for(int i=1;i<=n;++i) if(win[i]+lose[i]==n-1) ++ans;
    printf("%d\n",ans);
    return 0;
}
