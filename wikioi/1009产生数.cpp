#include<iostream>
#include<cstdio>
#include<string>
#include<queue>
#include<cstring>
using namespace std;
typedef long long LL;
const int INF=1<<20;
const int MAXSZ=30+5;
const int MAXK=15+5;
int mat[10][10];
char s[MAXSZ];
char rule[MAXK][2];
int k;
LL ans=1;

void floyd()
{
	for(int k=0;k<10;++k)
		for(int i=0;i<10;++i)
			for(int j=0;j<10;++j)
			{
				mat[i][j]=min(mat[i][j],mat[i][k]+mat[k][j]);
			}
}

int main()
{
	freopen("1.in","r",stdin);
	scanf("%s%d",s,&k);
	for(int i=0;i<10;++i)
		for(int j=0;j<10;++j)
			mat[i][j]=i==j?0:INF;
	for(int i=0;i<k;++i)
	{
		int t1,t2;
		scanf("%d%d",&t1,&t2);
		mat[t1][t2]=1;
	}
	floyd();
	int len=strlen(s);
	for(int i=0;i<len;++i)
	{
		int cnt=0,t=s[i]-'0';
		for(int j=0;j<10;++j)
		{
			if(j==t) continue;
			if(mat[t][j]<INF) ++cnt; 
		}
		++cnt;
		ans*=cnt;
	}
	cout<<ans<<endl;
	return 0;
}
