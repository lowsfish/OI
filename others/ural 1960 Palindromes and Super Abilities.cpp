#include<cstdio>
#include<cstring>
const int MAXN=100000+5;
const int SIGMA_SIZE=26;
struct Node{
	int num,len;
	Node* go[SIGMA_SIZE],*fail;
	Node():fail(0) {num=len=0;memset(go,0,sizeof(go));}
};
Node mem[MAXN],*cur=mem;
Node* root0,*root1;
Node* last;
void init()
{
	cur=mem;
	root0=cur++;
	root1=cur++;
	root0->fail=root1;
	root1->len=-1;
	last=root1;
}
inline Node* newNode(int len)
{
	cur->len=len;
	return cur++;
}
char s[MAXN];
int p=0;
inline Node* getFail(Node* t)
{
	while(s[p- t->len -1]!=s[p]) t=t->fail;
	return t;
}
int ans=0;
inline void extend(int w)
{
	++p;
	Node* t=getFail(last);
	if(!t->go[w])
	{
		Node* nt=newNode(t->len+2);
		t->go[w]=nt;
		if(t==root1) nt->fail=root0;
		else nt->fail=getFail(t->fail)->go[w];
		nt->num=nt->fail->num+1;
		++ans;
	}
	last=t->go[w];
	printf("%d",ans);
}
int main()
{
	init();
	scanf("%s",s+1);
	int n=strlen(s+1);
	s[0]='$';
	for(int i=1;i<=n;++i)
	{
		extend(s[i]-'a');
		if(i!=n) putchar(32);
		else putchar(10);
	}
	return 0;
}
