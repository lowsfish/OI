#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<cctype>
using namespace std;
const int MAXN=100+10;
const int MAXM=1000+10;
char s1[MAXN],s2[MAXM];

inline int idx(char c)
{
	c=tolower(c);
	return c-'a';
}

int main()
{
	scanf("%s%s",s1,s2);
	int m=strlen(s2),n=strlen(s1);
	for(int i=0;i<m;++i)
	{
		int j=i%n;
		int a=idx(s1[j]);
		if(idx(s2[i])<a) s2[i]=s2[i]-a+26;
		else s2[i]-=a;
	}
	printf("%s\n",s2);
	return 0;
}
