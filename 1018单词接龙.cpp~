#include<iostream>
#include<cstdio>
#include<cstring>
#define MAXN 25
#define MAXSZ 150
using namespace std;
char s[MAXN][MAXSZ],ans[MAXN*MAXSZ];
int len=0,mlen=0;
int n;
int used[MAXN];
int connect(int a,int b)
{
	int len,len1,len2;
	len1=strlen(s[a]);
	len2=strlen(s[b]);
	for(len=1;len<min(len1,len2);++len)
	{
		bool ok=1;
		int t;
		for(t=1;t<=len;++t)
		{
			if(s[a][len1-len+t-1]!=s[b][t-1]) {ok=0;break;}
		}
		if(ok) return len;

	}
	return 0;
}

void dfs(int t)
{
	if(len>mlen) mlen=len;
	for(int i=0;i<n;++i)
	{
		int nlen=connect(t,i);
		if(used[i]<2 && nlen)
		{
			++used[i];
			len+=strlen(s[i])-nlen;
			dfs(i);
			len-=strlen(s[i])-nlen;
			--used[i];
		}
	}
}
int main()
{
	freopen("1.in","r",stdin);
	char c;
	cin>>n;
	for(int i=0;i<n;++i) cin>>s[i];
	cin>>c;
	for(int i=0;i<n;++i)
	{
		if(s[i][0]==c) 
		{
			memset(used,0,sizeof(used));
			++used[i];
			len=strlen(s[i]);
			dfs(i);
		}
	}
	cout<<mlen;
//	cout<<connect(1,2);
}
