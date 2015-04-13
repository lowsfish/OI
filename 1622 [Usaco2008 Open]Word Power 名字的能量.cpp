#include<cstdio>
#include<cstring>
#include<cctype>
const int MAXN=1000+5;
const int MAXM=100+5;
int n,m;
char name[MAXN][MAXN];
char dict[MAXM][35];
inline int idx(char c)
{
	return c-'a';
}
inline bool judge(char* s1,char* s2)
{
	int p1=0,p2=0;
	int len1=strlen(s1),len2=strlen(s2);
	while(1)
	{
		if(s1[p1]==s2[p2]) ++p1,++p2;
		else ++p1;
		if(p2==len2) return 1;
		if(p1==len1) return 0;
	}
}
int main()
{
	freopen("1.in","r",stdin);
	scanf("%d%d",&n,&m);
	for(int i=0;i<n;++i)
	{
		scanf("%s",name[i]);
		int len=strlen(name[i]);
		for(int j=0;j<len;++j) 
			name[i][j]=tolower(name[i][j]);
	}
	for(int i=0;i<m;++i)
	{
		scanf("%s",dict[i]);
		int len=strlen(dict[i]);
		for(int j=0;j<len;++j)
			dict[i][j]=tolower(dict[i][j]);
	}
	for(int i=0;i<n;++i)
	{
		int cnt=0;
		for(int j=0;j<m;++j)
			if(judge(name[i],dict[j])) ++cnt;
		printf("%d\n",cnt);
	}
	return 0;
}
