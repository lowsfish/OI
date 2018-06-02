#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<map>
using namespace std;
map<int,int> ms;
const int MAXN=50000+10;
int a[MAXN];
int T;
int n;
int main()
{
	freopen("1.in","r",stdin);
	int T;
	scanf("%d",&T);
	while(T--)
	{
		bool flag=0;
		ms.clear();
		scanf("%d",&n);
		for(int i=0;i<n;++i) 
		{
			int t;
			scanf("%d",&t);
			if(!ms.count(t)) 
			{
				ms[t]=1;
				if(flag) putchar(' ');
				flag=1;
				printf("%d",t);
			}
		}
		putchar(10);
	}
	return 0;
}
