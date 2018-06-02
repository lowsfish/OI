#include<cstdio>
#include<algorithm>
#include<cstring>
const int MAXN=100000+5;
const int SIGMA_SIZE=26;
struct Node{
	Node* go[SIGMA_SIZE],*fail;
	int len;
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
inline Node* extend(int w)
{
	Node* t=getFail(last);
	if(!t->go[w])
	{
		Node* nt=newNode(t->len+2);
		t->go[w]=nt;
		if(t==root1) nt->fail=root0;
		else nt->fail=getFail(t->fail)->go[w];
	}
	return last=t->go[w];
}
inline int idx(char c)
{
	return c-'a';
}
Node* pt[MAXN];
int main()
{
//	freopen("1.in","r",stdin);
	init();
	scanf("%s",s+1);
	int n=strlen(s+1);
	s[0]='@';
	int ans=0;
	pt[0]=root0;
	for(p=1;p<=n;++p)
	{
		pt[p]=extend(idx(s[p]));
		ans=std::max(ans,pt[p]->len+pt[p- pt[p]->len]->len);
	}
	printf("%d\n",ans);
	return 0;
}
