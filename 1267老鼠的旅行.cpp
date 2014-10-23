#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
const int MAXSZ=25+5;
int f[MAXSZ][MAXSZ];
bool g[MAXSZ][MAXSZ];
int r,c,k;
int main()
{
	scanf("%d%d%d",&r,&c,&k);
	while(k--)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		--x;--y;
		g[x][y]=1;
	}
	f[0][0]=1;
	for(int i=1;i<r;++i) f[i][0]=g[i][0]?0:f[i-1][0];
	for(int i=1;i<c;++i) f[0][i]=g[0][i]?0:f[0][i-1];
	for(int i=1;i<r;++i)
		for(int j=1;j<c;++j)
		{
			if(g[i][j]) continue;
			f[i][j]=f[i-1][j]+f[i][j-1];
		}
	printf("%d\n",f[r-1][c-1]);
	return 0;
}
