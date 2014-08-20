#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
const int MAXV=26+26;
int mat[MAXV][MAXV];
int n;
const int INF=(1<<29)-1;
int idx(char c)
{
	if(c>='A' && c<='Z') return c-'A';
	else return c-'a'+26;
}

char getc(int i)
{
	if(i>=26) return 'a'+i-26;
	else return 'A'+i;
}
void init()
{
	for(int i=0;i<MAXV;++i)
		for(int j=0;j<MAXV;++j)
		{
			mat[i][j]=i==j?0:INF;
		}
}

void input()
{
	scanf("%d",&n);
	for(int i=0;i<n;++i)
	{
		getchar();
		char c1[5],c2[5];
		int cost;
		scanf("%s%s%d",c1,c2,&cost);
		int u=idx(c1[0]),v=idx(c2[0]);
		mat[u][v]=mat[v][u]=min(mat[u][v],cost);
	}
}

void floyd()
{
	for(int k=0;k<MAXV;++k)
		for(int i=0;i<MAXV;++i)
			for(int j=0;j<MAXV;++j)
			{
				mat[i][j]=min(mat[i][j],mat[i][k]+mat[k][j]);
			}
}

int main()
{
	freopen("1.in","r",stdin);
	init();
	input();
	floyd();
	int ans=INF,t;
	for(int i=0;i<25;++i)
	{
		if(mat[i][25]<ans)
		{
			ans=mat[i][25];
			t=i;
		}
	}
	printf("%c %d\n",getc(t),ans);
	return 0;
}
