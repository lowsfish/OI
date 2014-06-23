#include<iostream>
#include<cstdio>
#include<cstring>
#define M 20
using namespace std;
void build(char *s1,char *s2,char *s,int n)
{
	if(n<=0) return;
	char t;
	t=s1[n-1];
	s[0]=t;
	int p=strchr(s2,t)-s2;
	build(s1,s2,s+1,p);
	build(s1+p,s2+p+1,s+p+1,n-p-1);
}
int main()
{
	char s1[M];
	char s2[M];              //s2¿¿¿
	char s[M];
	cin>>s2>>s1;
	int n=strlen(s1); 
	build(s1,s2,s,n);
	s[n]=0;
	cout<<s;
	return 0;
}
