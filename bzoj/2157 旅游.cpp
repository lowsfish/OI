#include<cstdio>
#include<cstring>
#include<algorithm>
const int MAXN=200000+10;
const int INF=~0U>>1;
struct Node{
	int s,v;
	Node* p,*ch[2],*fa;
	int mx,mn,sum;
	bool rev,opp,isRoot;
	bool isAdd;
	Node() {mx=-INF;mn=INF;isRoot=v=s=sum=0;}
	inline void maintain()
	{
		s=ch[0]->s+ch[1]->s+1;
		mx=std::max(ch[0]->mx,ch[1]->mx);
		mn=std::min(ch[0]->mn,ch[1]->mn);
		if(isAdd)
		{
			mx=std::max(mx,v);
			mn=std::min(mn,v);
		}
		sum=v+ch[0]->sum+ch[1]->sum;
	}
	inline void setc(Node* t,bool d)
	{
		ch[d]=t;
		t->p=this;
	}
	inline bool d()const {return p->ch[1]==this;}
	inline void pushdown();
	inline void revIt()
	{
		rev^=1;
		std::swap(ch[0],ch[1]);
	}
	inline void makeOpp()
	{
		opp^=1;
		sum=-sum;v=-v;
		std::swap(mx,mn);
		mx=-mx;mn=-mn;
	}
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
	if(opp)
	{
		if(ch[0]!=null) ch[0]->makeOpp();
		if(ch[1]!=null) ch[1]->makeOpp();
		opp=0;
	}
}
inline void Node::setRoot(Node* f)
{
	isRoot=1;
	fa=f;
	p=null;
}
inline Node* NewNode(int v,bool isAdd)
{
	C->v=v;C->s=1;
	C->sum=C->mx=C->mn=v;
	C->isRoot=1;
	C->p=C->fa=C->ch[0]=C->ch[1]=null;
	C->isAdd=isAdd;
	return C++;
}
inline void rot(Node* t)
{
	Node* p=t->p;
	p->pushdown();t->pushdown();
	bool d=t->d();
	p->p->setc(t,t->p->d());
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
	for(int i=top-1;i>=0;--i) stk[i]->pushdown();
}
void splay(Node* t,Node* f=null)
{
	pushTo(t);
	while(t->p!=f)
	{
		if(t->p->p==f) rot(t);
		else t->d()==t->p->d()?(rot(t->p),rot(t)):(rot(t),rot(t));
	}
	t->maintain();
}
void access(Node* t)
{
	Node* v;
	for(v=null;t!=null;v=t,t=t->fa)
	{
		splay(t);
		t->ch[1]->setRoot(t);
		t->setc(v,1);
		v->fa=t;
	}
}
inline void makeRoot(Node* t)
{
	access(t);
	splay(t);
	t->revIt();
}
inline void getPath(Node* u,Node* v)
{
	makeRoot(u);
	access(v);
	splay(v);
}
inline void addEdge(Node* u,Node* v)
{
	makeRoot(v);v->fa=u;
}
int n,m;
Node* pt[MAXN];
int main()
{
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	scanf("%d",&n);
	for(int i=1;i<n;++i)
	{
		int u,v,w;
		scanf("%d%d%d",&u,&v,&w);
		pt[i+n]=NewNode(w,1);
		if(!pt[u]) pt[u]=NewNode(0,0);
		if(!pt[v]) pt[v]=NewNode(0,0);
		addEdge(pt[u],pt[i+n]);
		addEdge(pt[v],pt[i+n]);
	}
	scanf("%d",&m);
	char s[20];
	int a,b;
	while(m--)
	{
		scanf("%s%d%d",s,&a,&b);
		if(s[0]=='C') splay(pt[a+n]),pt[a+n]->v=b,pt[a+n]->maintain();
		else if(s[0]=='N') getPath(pt[a],pt[b]),pt[b]->makeOpp();
		else if(s[0]=='S') getPath(pt[a],pt[b]),printf("%d\n",pt[b]->sum);
		else if(s[1]=='A') getPath(pt[a],pt[b]),printf("%d\n",pt[b]->mx);
		else getPath(pt[a],pt[b]),printf("%d\n",pt[b]->mn);
	}
	return 0;
}
