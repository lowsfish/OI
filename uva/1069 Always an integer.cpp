#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cctype>
#define rep(i,n) for(int i=0;i<n;++i)
typedef long long LL;
const int MAXL=100000+5;
int pow_mod(int a,int b,int mod)
{
	LL base=a,ans=1;
	while(b)
	{
		if(b&1) ans=ans*base%mod;
		base=base*base%mod;
		b>>=1;
	}
	return ans;
}
int pos,D=0,len;
char s[MAXL];
inline int cal(int n)
{
	int sign=1,xi=1;
	if(s[pos]=='-') sign=-1,++pos;
	if(s[pos]=='+') ++pos;
	if(isdigit(s[pos])) xi=0;
	while(isdigit(s[pos])) xi=xi*10+s[pos++]-'0';
	if(s[pos]!='n') return sign*xi;
	++pos;
	if(s[pos]!='^') return (int)((LL)n*(LL)xi*sign%D);
	++pos;
	int p=0;
	while(isdigit(s[pos])) p=p*10+s[pos++]-'0';
	int temp=pow_mod(n,p,D);
	return (int)((LL)temp*(LL)xi*sign%D);
}
bool judge()
{
	int p=strchr(s,')')-s,temp=p+2;
	D=0;len=strlen(s);
	while(temp<len) D=D*10+s[temp++]-'0';
	int maxk=0;
	rep(i,p) if(s[i]=='^')
	{
		++i;
		while(isdigit(s[i])) maxk=maxk*10+s[i++]-'0';
		break;
	}
	rep(i,maxk+1)
	{
		LL ans=0;
		pos=1;
		while(pos<p) ans=ans+cal(i+1)%D;
		if(ans%D != 0) return 0;
	}
	return 1;
}
char s1[50]="Always an integer\0",s2[50]="Not always an integer\0";
int main()
{
	//freopen("1.in","r",stdin);
	int kase=0;
	while(scanf("%s",s)!=EOF && s[0]!='.')
		printf("Case %d: %s\n",++kase,judge()?s1:s2);
	return 0;
}
