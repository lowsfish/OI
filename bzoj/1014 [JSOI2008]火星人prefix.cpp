#include<cstdio>
#include<cstring>
#include<algorithm>
const int MAXN=100000+10,seed=13331;
typedef unsigned long long ull;
char s[MAXN];
int n,m;
ull P[MAXN];
struct Node{
	Node* p,*ch[2];
	ull key;
	int s,v;
	Node() {s=key=v=0;ch[0]=ch[1]=0;}
	inline bool d() const
	{
		return p->ch[1]==this;
	}
	inline void setc(Node* t,bool d)
	{
		ch[d]=t;
		t->p=this;
	}
	inline void maintain()
	{
		s=ch[0]->s+ch[1]->s+1;
		ull t=ch[0]->key;
		t*=seed;
		t+=v;
		t*=P[ch[1]->s];
		t+=ch[1]->key;
		key=t;
	}
}Tnull,*null=&Tnull;
Node mem[MAXN],*C=mem;
Node* root;
inline Node* newNode(int v)
{
	C->v=v;C->key=(ull)v;
	C->s=1;
	C->ch[0]=C->ch[1]=null;
	return C++;
}
inline void rotate(Node* t)
{
	Node* p=t->p;
	bool d=t->d();
	p->p->setc(t,p->d());
	p->setc(t->ch[d^1],d);
	t->setc(p,d^1);
	p->maintain();
	if(p==root) root=t;
}
inline void splay(Node* t,Node* f=null)
{
	while(t->p!=f)
	{
		if(t->p->p==f) rotate(t);
		else t->d()==t->p->d()?(rotate(t->p),rotate(t)):(rotate(t),rotate(t));
	}
	t->maintain();
}
inline Node* select(int k)
{
	for(Node* t=root;;)
	{
		int s=t->ch[0]->s;
		if(s==k) return t;
		if(k>s) k-=s+1,t=t->ch[1];
		else t=t->ch[0];
	}
}
inline void splay(int k,Node* f=null)
{
	splay(select(k),f);
}
inline Node*& get(int l,int r)	//[l,r)
{
	splay(l-1);
	splay(r,root);
	return root->ch[1]->ch[0];
}
inline void insert(int p,int x)
{
	get(p+1,p+1);
	Node* t=newNode(x);
	root->ch[1]->setc(t,0);
	splay(t);
}
inline void change(int p,int x)
{
	Node* t=get(p,p+1);
	t->v=x;t->key=x;
	splay(t);
}
inline ull hash(int l,int r)
{
	return get(l,r+1)->key;
}
inline int query(int a,int b)
{
	int ans=0,sz=root->s-1;
	for(int i=1<<17;i;i>>=1)
	{
		if(a+i<=sz && b+i<=sz && hash(a,a+i-1)==hash(b,b+i-1))	//要判断单个字符
			ans+=i,a+=i,b+=i;
	}
	return ans;
}
Node* build(int l,int r)	//[l,r)
{
	if(l>=r) return null;
	int m=(l+r)>>1;
	Node* t=newNode(s[m]);
	t->setc(build(l,m),0);
	t->setc(build(m+1,r),1);
	t->maintain();
	return t;
}
void init()
{
	C=mem;
	root=build(0,n+2);
	root->p=null;
}
int main()
{
//	freopen("1.in","r",stdin);
	scanf("%s",s+1);
	n=strlen(s+1);
	P[0]=1;
	for(int i=1;i<MAXN;++i) P[i]=P[i-1]*seed;
	s[0]=s[n+1]=0;
	init();
	char cmd[5];
	scanf("%d",&m);
	while(m--)
	{
		int a,b;
		char c;
		scanf("%s",cmd);
		switch(cmd[0])
		{
			case 'Q':scanf("%d%d",&a,&b);
					 printf("%d\n",query(a,b));
					 break;
			case 'R':scanf("%d %c",&a,&c);
					 change(a,(int)c);
					 break;
			case 'I':scanf("%d %c",&a,&c);
					 insert(a,(int)c);
					 break;
		}
	}
	return 0;
}
