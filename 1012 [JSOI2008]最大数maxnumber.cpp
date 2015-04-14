#include<cstdio>
#include<algorithm>
const int MAXN=200000+5;
int n,mod,t;
int top,len,st[MAXN],a[MAXN];
int main()
{
	char s[5];
	scanf("%d%d",&n,&mod);
	while(n--)
	{
		int x;
		scanf("%s%d",s,&x);
		if(s[0]=='A')
		{
			x=(x+t)%mod;
			a[len]=x;
			while(top && a[st[top-1]]<=x) --top;
			st[top++]=len++;
		}
		else
		{
			int t1=std::lower_bound(st,st+top,len-x)-st;
			printf("%d\n",t=a[st[t1]]);
		}
	}
	return 0;
}
