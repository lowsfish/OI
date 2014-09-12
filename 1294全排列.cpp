#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=10+10;
int a[10];
int main()
{
	int n;
	scanf("%d",&n);
	for(int i=0;i<n;++i) a[i]=i+1;
	do
	{
		for(int i=0;i<n;++i)
		{
			printf("%d",a[i]);
			if(i!=n-1) putchar(' ');
		}
		putchar(10);
	}while(next_permutation(a,a+n));
	return 0;
}
