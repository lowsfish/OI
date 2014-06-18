#include<iostream>
#include<cstdio>
#include<cstring>
#define M 1000001
using namespace std;
char t[M];
int f[M];
void getfail()
{
	int len=strlen(t),i,j;
	memset(f,0,sizeof(f));
	for(i=1;i<len;++i)
	{
		j=f[i];
		while(j&&t[i]!=t[j]) j=f[j];
		f[i+1]=t[i]==t[j]?j+1:0;
	}
}

int work()
{
	int len=strlen(t);

	int j=len-f[len];
	if(len%j==0) return len/j;
	return 1;
}
int main()
{
	ios::sync_with_stdio(false);
	while(cin>>t)
	{
		if(t[0]=='.') break;
		getfail();
		cout<<work()<<endl;
	}
	return 0;
}
