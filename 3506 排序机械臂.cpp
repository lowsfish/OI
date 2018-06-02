#include<cstdio>
#include<algorithm>
const int MAXN=100000+10;
const int INF=~0U>>1;
int a[MAXN];
struct Node{
	int s,v;
	bool rev;
	Node* p,*ch[2],*minn;
	Node() {s=rev=0;v=INF;minn=this;}
	inline bool d() {return p->ch[1]==this;}
	inline void maintain();
	inline void revIt()
	{
		std::swap(ch[0],ch[1]);
		rev^=1;
	}
	inline void setc(Node* t,bool d)
	{
		ch[d]=t;
		t->p=this;
	}
	inline void pushdown();
}Tnull,*null=&Tnull;
Node mem[MAXN],*C=mem;
Node* root;
struct met{
	Node* temp;
	int pos;
	bool operator<(const met& rhs)const
	{
		return temp->v < rhs.temp->v ||(rhs.temp->v == temp->v && pos<rhs.pos);
	}
}h[MAXN];
inline Node* Min(Node* a,Node* b)
{
	return a->v <= b->v ?a:b;
}
inline void Node::pushdown()
{
	if(rev)
	{
		if(ch[0]!=null) ch[0]->revIt();
		if(ch[1]!=null) ch[1]->revIt();
		rev=0;
	}
}
inline void Node::maintain()
{
	s=ch[0]->s+ch[1]->s+1;
	minn=Min(Min(ch[0]->minn,this),ch[1]->minn);
}
inline void init()
{
	C=mem;
}
inline Node* NewNode(int v)
{
	C->v=v;C->s=1;
	C->ch[0]=C->ch[1]=null;
	return C++;
}
Node* build(int l,int r) //[l,r)
{
	if(l>=r) return null;
	int m=l+r>>1;
	Node* t=NewNode(a[m]);
	h[m].temp=t;h[m].pos=m;
	Node* L=build(l,m),*R=build(m+1,r);
	t->setc(L,0);t->setc(R,1);
	t->maintain();
	return t;
}
void rot(Node* t)
{
	Node* p=t->p;
	p->pushdown();t->pushdown();
	int d=t->d();
	p->p->setc(t,p->d());
	p->setc(t->ch[d^1],d);
	t->setc(p,d^1);
	p->maintain();
	if(p==root) root=t;
}
void splay(Node* t,Node* f=null)
{
	while(t->p!=f)
	{
		if(t->p->p==f) rot(t);
		else
			t->d()==t->p->d()?(rot(t->p),rot(t)):(rot(t),rot(t));
	}
	t->maintain();
}
Node* select(int k)
{
	for(Node* t=root;;)
	{
		t->pushdown();
		int s=t->ch[0]->s;
		if(k==s) return t;
		if(k>s) k-=s+1,t=t->ch[1];
		else t=t->ch[0];
	}
}
inline void splay(int k,Node* f=null)
{
	splay(select(k),f);
}
Node*& get(int l,int r)
{
	Node* L=select(l-1);
	Node* R=select(r);
	splay(L);
	splay(R,L);
	return R->ch[0];
}
int DelMin(int i)
{
	splay(h[i].temp);
	int s=root->ch[0]->s;
	Node*& t=get(1,s);
	t->revIt();
	splay(s-1);
	splay(s+1,root);
	root->ch[1]->ch[0]=null;
	root->ch[1]->maintain();
	root->maintain();
	return s;
}
void debug(Node* t)
{
	if(t==null) return;
	debug(t->ch[0]);
	printf("%d ",t->v);
	debug(t->ch[1]);
}
int n;
int main()
{
//	freopen("1.in","r",stdin);
//	freopen("1.out","w",stdout);
	while(scanf("%d",&n)!=EOF && n)
	{
		a[0]=a[n+1]=INF;
		init();
		for(int i=1;i<=n;++i) scanf("%d",a+i);
		root=build(0,n+2);
		root->p=null;
		std::sort(h+1,h+n+1);
		for(int i=0;i<n;++i)
		{
			printf("%d%c",DelMin(i+1)+i,i==n-1?'\n':' ');
			//debug(root),putchar(10);
		}
	}
	return 0;
}
