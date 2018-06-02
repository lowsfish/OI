#include<cstdio>
#include<algorithm>
#include<vector>
const int MOD=51061;
const int MAXN=100000+10;
typedef long long int64;
struct Mark{
	int64 mul,add;
	Mark(int64 mu,int64 ad):mul(mu),add(ad) {}
	Mark() {mul=1;add=0;}
	inline bool needPush() {return mul!=1 || add!=0;}
};
Mark operator*(Mark a,Mark b)
{
	return Mark(a.mul*b.mul%MOD,(a.add*b.mul+b.add)%MOD);
}
struct Node{
	int s;
	bool rev,isRoot;
	Mark m;
	int64 sum,v;
	Node* p,*fa,*ch[2];
	Node() {s=isRoot=sum=0;}
	inline bool d()const {return p->ch[1]==this;}
	inline void setc(Node* t,bool d)
	{
		ch[d]=t;
		t->p=this;
	}
	inline void maintain()
	{
		s=ch[0]->s+ch[1]->s+1;
		sum=(ch[0]->sum+ch[1]->sum+v)%MOD;
	}
	inline void revIt()
	{
		rev^=1;
		std::swap(ch[0],ch[1]);
	}
	inline void apply(Mark a)
	{
		m=m*a;
		sum=(sum*a.mul+a.add*s)%MOD;
		v=(v*a.mul+a.add)%MOD;
	}
	inline void pushdown();
	inline void setRoot(Node* f);
}Tnull,*null=&Tnull;
Node mem[MAXN],*C=mem;
inline void Node::pushdown()
{
	if(rev)
	{
		if(ch[0]!=null) ch[0]->revIt();
		if(ch[1]!=null) ch[1]->revIt();
		rev=0;
	}
	if(m.needPush())
	{
		if(ch[0]!=null) ch[0]->apply(m);
		if(ch[1]!=null) ch[1]->apply(m);
		m=Mark();
	}
}
inline void Node::setRoot(Node* f)
{
	isRoot=1;
	fa=f;
	p=null;
}
inline Node* newNode(int v)
{
	C->p=C->fa=C->ch[0]=C->ch[1]=null;
	C->s=1;
	C->m=Mark();
	C->v=C->sum=v;
	C->isRoot=1;
	C->rev=0;
	return C++;
}
inline void rot(Node* t)
{
	Node* p=t->p;
	p->pushdown();t->pushdown();
	bool d=t->d();
	p->p->setc(t,p->d());
	p->setc(t->ch[d^1],d);
	t->setc(p,d^1);
	p->maintain();
	if(p->isRoot)
	{
		p->isRoot=0;
		t->isRoot=1;
		t->fa=p->fa;
	}
}
void pushTo(Node* t)
{
	static Node* stk[MAXN];
	int top=0;
	while(t!=null)
	{
		stk[top++]=t;
		t=t->p;
	}
	while(top) stk[--top]->pushdown();
}
void splay(Node* t,Node* f=null)
{
//	pushTo(t);
	t->pushdown();
	while(t->p!=f)
	{
		if(t->p->p==f) rot(t);
		else t->d()==t->p->d()?(rot(t->p),rot(t)):(rot(t),rot(t));
	}
	t->maintain();
}
Node* access(Node* u)
{
	for(Node* v=null;u!=null;v=u,u=u->fa)
	{
		splay(u);
		u->ch[1]->setRoot(u);
		u->setc(v,1);
		v->fa=u;
	}
}
inline void makeRoot(Node* u)
{
	access(u);
	splay(u);
	u->revIt();
}
inline void delEdge(Node* u,Node* v)
{
	makeRoot(u);
	access(v);
	splay(u);
	u->setc(null,1);
	u->maintain();
	v->fa=v->p=null;
	v->isRoot=1;
}
inline void addEdge(Node* u,Node* v)
{
	makeRoot(v);
	v->fa=u;
}
inline void getPath(Node* u,Node* v)
{
	makeRoot(u);
	access(v);
	splay(v);
}
inline void modify(Node* u,Node* v,Mark a)
{
	getPath(u,v);
	v->apply(a);
}
inline int queryPath(Node* u,Node* v)
{
	getPath(u,v);
	return v->sum;
}
int n,q;
Node* pt[MAXN];
int fa[MAXN],que[MAXN];;
std::vector<int> G[MAXN];
typedef std::vector<int>::iterator it;
void bfs()
{
	int head=0,tail=0;
	que[tail++]=0;fa[0]=-1;
	while(head<tail)
	{
		int u=que[head++];
		for(it e=G[u].begin();e!=G[u].end();++e)
			if(*e!=fa[u]) fa[*e]=u,pt[*e]->fa=pt[u],que[tail++]=*e;
	}
}
int main()
{
	int u,v,t1,t2;
	scanf("%d%d",&n,&q);
	for(int i=0;i<n;++i) pt[i]=newNode(1);
	for(int i=0;i<n-1;++i)
	{
		scanf("%d%d",&u,&v);
		--u;--v;
		G[u].push_back(v);
		G[v].push_back(u);
//		addEdge(pt[u],pt[v]);
	}
	bfs();
	char s[5];
	while(q--)
	{
		scanf("%s%d%d",s,&u,&v);
		--u;--v;
		switch(s[0])
		{
			case '+':scanf("%d",&t1);
					 modify(pt[u],pt[v],Mark(1,t1));
					 break;
			case '-':scanf("%d%d",&t1,&t2);
					 delEdge(pt[u],pt[v]);
					 addEdge(pt[--t1],pt[--t2]);
					 break;
			case '*':scanf("%d",&t1);
					 modify(pt[u],pt[v],Mark(t1,0));
					 break;
			default: printf("%d\n",queryPath(pt[u],pt[v]));
		}
	}
	return 0;
}
