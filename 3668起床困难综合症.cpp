#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
const int MAXN=100000+10;
struct opt{
	char op[5];
	int x;
}op[MAXN];

inline int getans(opt t,int x)
{
	if(t.op[0]=='A') return x&t.x;
	if(t.op[0]=='X') return x^t.x;
	if(t.op[0]=='O') return x|t.x;
}
int m,n,ans=0;
int main()
{
	//freopen("1.in","r",stdin);
	int log=0;
	scanf("%d%d",&n,&m);
	for(int i=0;i<n;++i) scanf("%s%d",op[i].op,&op[i].x);
	while((1<<log)<=m) ++log;--log;
	for(int i=log;i>=0;--i)
	{
		int t=0;
		if(ans+(1<<i)>m) continue;
		for(int j=0;j<n;++j) t=getans(op[j],t);
		if(t&(1<<i)) continue;
		t=1<<i;
		for(int j=0;j<n;++j) t=getans(op[j],t);
		if(t&(1<<i)) ans+=1<<i;
	}
	for(int i=0;i<n;++i) ans=getans(op[i],ans);
	printf("%d\n",ans);
	return 0;
}
