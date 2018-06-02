#include<iostream>
#include<cstdio>
#include<cstring>
#define M 100
using namespace std;
int n;
void add(char *s1,char *s2,char *ans)
{
	int a[M],b[M],len1=strlen(s1),len2=strlen(s1),i;
	int c[M];
	memset(a,0,sizeof(a));
	memset(b,0,sizeof(b));
	memset(c,0,sizeof(c));
	memset(ans,0,sizeof(ans));
	for(i=0;i<len1;++i)
	{
		if(s1[i]>'9') a[len1-i-1]=s1[i]-'A'+10;
		else a[len1-i-1]=s1[i]-'0';
	}
	for(i=0;i<len2;++i)
	{
		if(s2[i]>'9') b[len2-i-1]=s2[i]-'A'+10;
		else b[len2-i-1]=s2[i]-'0';
	}

	i=0;
	int x=0;
	while(i<len1 || i<len2)
	{
		c[i]=a[i]+b[i]+x;
		x=c[i]/n;
		c[i]%=n;
		++i;
	}
	if(x==1) c[i]=1;
	else --i;
	int len3=i;
	for(i=0;i<=len3;++i)
	{
		if(c[i]>=10) ans[len3-i]=c[i]-10+'A';
		else ans[len3-i]=c[i]+'0';
	}
	ans[len3+1]=0;
}

bool judge(char *s)
{
	int i,len=strlen(s);
	for(i=0;i<(len>>1);++i)
		if(s[i]!=s[len-i-1]) return 0;
	return 1;
}

void turn(char *s,char *s1)
{
	int len=strlen(s);
	for(int i=0;i<len;++i)
	{
		s1[i]=s[len-i-1];
	}
	s1[len]=0;
}
int main()
{
	freopen("1.in","r",stdin);
	char s1[M],s2[M],s[M];
	int cnt=0;
	cin>>n;
	cin>>s1;
	if(judge(s1))
	{
		cout<<"STEP=0";
		return 0;
	}
	turn(s1,s2);
	do
	{
		add(s1,s2,s);
		++cnt;
//		cout<<s<<endl;
		if(cnt>=30) 
		{
			cout<<"Impossible!";
			return 0;
		}
		if(judge(s)) 
		{
			cout<<"STEP="<<cnt<<endl;
			return 0;
		}
		strcpy(s1,s);
		turn(s1,s2);
	}while(1);
	return 0;
}
