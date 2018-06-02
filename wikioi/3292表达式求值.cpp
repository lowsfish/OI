#include<iostream>
#include<cstdio>
#include<cstring>
#include<stack>
#include<cctype>
const int MAXSZ=20000000+10;
const int MOD=10000;
using namespace std;
typedef long long LL;
stack<char> ops;
stack<LL> nus;
char p[MAXSZ];

inline int priority(char c)
{
	if(c=='*' || c=='/') return 2;
	if(c=='-' || c=='+') return 1;
	return 0;
}

void po()
{
	LL a=nus.top();nus.pop();
	LL b=nus.top();nus.pop();
	char c=ops.top();ops.pop();
	switch(c)
	{
		case '+':a+=b;
				 a%=MOD;
				 nus.push(a);
				 break;
		case '-':b-=a;
				 nus.push(b);
				 break;
		case '*':b*=a;
				 b%=MOD;
				 nus.push(b);
				 break;
		case '/':b/=a;
				 nus.push(b);
				 break;
	}

}
void ins()
{
	int n=strlen(p);
	for(int i=0;i<n;++i)
	{
		if(isdigit(p[i]))
		{
			LL x=p[i]-'0';
			while(isdigit(p[i+1]))
			{
				x=x*10+p[++i]-'0';
				x%=MOD;
			}
			nus.push(x);
		}
		else if(p[i]=='(') ops.push(p[i]);
		else if(p[i]==')')
		{
			while(!ops.empty())
			{
				if(ops.top()=='(')
				{
					ops.pop();
					break;
				}
				po();
			}
		}
		else if(ops.empty() || priority(p[i])>priority(ops.top())) ops.push(p[i]);
		else 
		{
			while(!ops.empty() && priority(ops.top())>=priority(p[i])) po();	
			ops.push(p[i]);
		}
	}
}

int getans()
{
	while(!ops.empty()) po();
	/*while(!ops.empty()) 
	{
		putchar(ops.top());
		ops.pop();
	}
	putchar(10);
	while(!nus.empty()) 
	{
		printf("%f ",nus.top());
		nus.pop();
	}*/
	LL ans=nus.top();nus.pop();
	return ans%MOD;
}

int main()
{
	freopen("1.in","r",stdin);
	scanf("%s",p);
	ins();
	printf("%d\n",getans());
//	getans();
	return 0;
}
