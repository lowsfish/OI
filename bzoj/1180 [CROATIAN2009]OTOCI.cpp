#include<cstdio>
#include<algorithm>
#define rep(i,n) for(int i=0;i<n;++i)
const int MAXN=30000+10;
const int INF=~0U>>1;
struct Node{
	int v,sum;
	bool rev;
	Node*p,*ch[2];
	Node() {v=sum=rev=0;}
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
		sum=v+ch[0]->sum+ch[1]->sum;
	}
	inline void revIt()
	{
		rev^=1;
		std::swap(ch[0],ch[1]);
	}
	inline bool isRoot() const;
	inline void pushdown();
}Tnull,*null=&Tnull;
inline bool Node::isRoot()const
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
	p->maintain();
}
inline void splay(Node* t)
{
	t->pushdown();
	while(!t->isRoot())
	{
		if(t->p->isRoot()) rot(t);
		else t->d()==t->p->d()?(rot(t->p),rot(t)):(rot(t),rot(t));
	}
	t->maintain();
}
inline void access(Node* u)
{
	for(Node* v=null;u!=null;v=u,u=u->p)
	{
		splay(u);
		u->setc(v,1);
		u->maintain();
	}
}
inline void makeRoot(Node* u)
{
	access(u);
	splay(u);
	u->revIt();
}
inline Node* getRoot(Node* u)
{
	for(;u->p!=null;u=u->p);
	return u;
}
inline void link(Node* u,Node* v)
{
	makeRoot(u);
	u->p=v;
}
inline void change(Node* u,int v)
{
	access(u);
	splay(u);
	u->v=v;
	u->maintain();
}
inline int getSum(Node* u,Node* v)
{
	makeRoot(u);
	access(v);
	splay(v);
	return v->sum;
}
Node mem[MAXN],*C=mem;
Node* newNode(int x)
{
	C->v=C->sum=x;
	C->ch[0]=C->ch[1]=C->p=null;
	C->rev=0;
	return C++;
}
Node* pt[MAXN];
int n,q,w;
int main()
{
	freopen("1.in","r",stdin);
	scanf("%d",&n);
	rep(i,n) scanf("%d",&w),pt[i+1]=newNode(w);
	scanf("%d",&q);
	char s[20];
	int u,v;
	while(q--)
	{
		scanf("%s%d%d",s,&u,&v);
		switch(s[0])
		{
			case 'b':if(getRoot(pt[u])==getRoot(pt[v])) printf("no\n");
					 else printf("yes\n"),link(pt[u],pt[v]);
					 break;
			case 'p':change(pt[u],v);
					 break;
			case 'e':if(getRoot(pt[u])!=getRoot(pt[v])) printf("impossible\n");
					 else printf("%d\n",getSum(pt[u],pt[v]));
					 break;
		}
	}
	return 0;
}
