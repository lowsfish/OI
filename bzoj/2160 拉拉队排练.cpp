#include<cstdio>
#include<cstring>
#include<algorithm>
#define fr first
#define sc second
const int MAXN=1000000+5;
const int SIGMA_SIZE=26;
const int MOD=19930726;
typedef std::pair<int,int> P;
struct Node{
	Node* fail,*go[SIGMA_SIZE];
	int len,cnt;
};
Node mem[MAXN],*cur;
Node* root0,*root1,*last;
void init()
{
	cur=mem;
	root0=cur++;
	root1=cur++;
	root1->len=-1;
	root0->fail=root1;
	last=root1;
}
inline Node* newNode(int len)
{
	cur->len=len;
	return cur++;
}
char s[MAXN];
int p;
inline Node* getFail(Node* t)
{
	while(s[p- t->len -1]!=s[p]) t=t->fail;
	return t;
}
inline void extend(int w)
{
	Node* t=getFail(last);
	if(!t->go[w])
	{
		Node* nt=newNode(t->len+2);
		t->go[w]=nt;
		if(t==root1) nt->fail=root0;
		else nt->fail=getFail(t->fail)->go[w];
	}
	(last=t->go[w])->cnt++;
}
inline int pow_mod(int a,int b)
{
	long long ans=1;
	for(;b;b>>=1,a=a*a%MOD)
		if(b&1) ans=ans*a%MOD;
	return (int)ans;
}
int n;
P a[MAXN];
int p1=0;
long long tot=0,k;
inline int idx(char c)
{
	return c-'a';
}
void work()
{
	for(Node* t=cur-1;t>=mem+2;--t)
	{
		t->fail->cnt+=t->cnt;
		a[p1++]=P(t->len,t->cnt);
		tot+=t->cnt;
	}
	if(tot<k) printf("-1\n");
	else
	{
		
		std::sort(a,a+p1);
		long long ago=1;
		for(int i=p1-1;i>=0;--i)
		{
			int now=std::min(k,(long long)a[i].sc);
			ago=ago*pow_mod(a[i].fr,now)%MOD;
			k-=now;
			if(k==0) break;
		}
		printf("%lld\n",ago);
	}
}
int main()
{
	//freopen("1.in","r",stdin);
	init();
	scanf("%d%lld%s",&n,&k,s+1);
	s[0]='@';
	for(p=1;p<=n;++p) extend(idx(s[p]));
	work();
	return 0;
}
