#include<cstdio>
#include<algorithm>
#define rep(i,n) for(int i=0;i<n;++i)
const int MAXN=10000+5;
const int INF=~0U>>1;
struct Node{
	Node* p,*ch[2];
	bool rev;
	Node() {rev=0;}
	inline bool d() const
	{
		return this==p->ch[1];
	}
	inline void setc(Node* t,bool d)
	{
		ch[d]=t;
		t->p=this;
	}
	inline void revIt()
	{
		rev^=1;
		std::swap(ch[0],ch[1]);
	}
	inline bool isRoot() const;
	inline void pushdown();
}Tnull,*null=&Tnull;
inline bool Node::isRoot() const
{
	return p==null || (p->ch[0]!=this && p->ch[1]!=this);
}
inline void Node::pushdown()
{
	if(rev)
	{
		rev=0;
		rep(i,2) if(ch[i]!=null)
			ch[i]->revIt();
	}
}
inline void rot(Node* t)
{
	Node* p=t->p;
	p->pushdown();t->pushdown();
	bool d=t->d();
	if(!p->isRoot()) p->p->setc(t,p->d());
	else t->p=p->p;
	p->setc(t->ch[d^1],d);
	t->setc(p,d^1);
}
inline void splay(Node* t)
{
	t->pushdown();
	while(!t->isRoot())
	{
		if(t->p->isRoot()) rot(t);
		else t->d()==t->p->d()?(rot(t->p),rot(t)):(rot(t),rot(t));
	}
}
inline void access(Node* u)
{
	for(Node* v=null;u!=null;v=u,u=u->p)
	{
		splay(u);
		u->setc(v,1);
	}
}
inline void makeRoot(Node* u)
{
	access(u);
	splay(u);
	u->revIt();
}
inline void link(Node* u,Node* v)
{
	makeRoot(u);
	u->p=v;
}
inline void cut(Node* u,Node* v)
{
	makeRoot(u);
	access(v);
	splay(v);
	v->setc(null,0);
	u->p=null;
}
inline Node* getRoot(Node* u)
{
	for(;u->p!=null;u=u->p);
	return u;
}
int n,m;
Node mem[MAXN],*C=mem;
inline Node* newNode()
{
	C->p=C->ch[0]=C->ch[1]=null;
	C->rev=0;
	return C++;
}
Node* pt[MAXN];
int main()
{
	freopen("1.in","r",stdin);
	scanf("%d%d",&n,&m);
	rep(i,n) pt[i+1]=newNode();
	char s[10];
	int u,v;
	while(m--)
	{
		scanf("%s%d%d",s,&u,&v);
		switch(s[0])
		{
			case 'Q':if(getRoot(pt[u])==getRoot(pt[v])) printf("Yes\n");
					 else printf("No\n");
					 break;
			case 'C':link(pt[u],pt[v]);
					 break;
			case 'D':cut(pt[u],pt[v]);
					 break;
		}
	}
	return 0;
}
