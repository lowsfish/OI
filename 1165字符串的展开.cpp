#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cctype>
using namespace std;
const int MAXN=100+10;
int p1,p2,p3,i;
char s[MAXN];
void solve()
{
	if(s[i]==s[i+2]-1){

		return;
	}
	int d=s[i+2]-s[i]-1;
	if(p1==3)
	{
		for(int i=0;i<d*p2;++i) putchar('*');
		return;
	}
	int x,y;
	if(p1==1 || isdigit(s[i]))
		x=s[i]+1,y=s[i+2]-1;
	else
		x=s[i]+1-32,y=s[i+2]-1-32;
	if(p3==1)
	{
		for(int j=x;j<=y;++j)
		{
			for(int k=0;k<p2;++k)
			{
				putchar(j);
			}
		}
	}
	else
	{
		for(int j=y;j>=x;--j)
		{
			for(int k=0;k<p2;++k)
			{
				putchar(j);
			}
		}
	}
}

int main()
{
	scanf("%d%d%d",&p1,&p2,&p3);
	scanf("%s",s);
	int n=strlen(s);
	for(i=0;i<n;++i)
	{
        putchar(s[i]);
		if(i<n-1 && s[i+1]=='-' && (isdigit(s[i]) && isdigit(s[i+2]) || isalpha(s[i]) && isalpha(s[i+2])) && s[i]<s[i+2])
		{
			solve();
			i++;
		}
	}
	return 0;
}
