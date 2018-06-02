#include<cstdio>
#include<cstring>
#include<algorithm>
const int MAXN=600000+5;
const int MAXQ=3000000+5;
const int SIGMA_SIZE=26;
inline int idx(char c)
{	return c-'A';	}
namespace LCT{
	struct Node{
		Node* p,*ch[2];
		int cnt,add;
		Node() {cnt=add=0;p=ch[0]=ch[1]=0;}
		inline bool d() const
		{	return p->ch[1]==this;	}
		inline void setc(Node* t,bool d)
		{
			ch[d]=t;
			t->p=this;
		}
		inline void addIt(int ad)
		{
			add+=ad;
			cnt+=ad;
		}
		inline void pushdown();
		inline bool isRoot() const;
	}*null;
	inline void Node::pushdown()
	{
		if(add)
		{
			if(ch[0]!=null) ch[0]->addIt(add);
			if(ch[1]!=null) ch[1]->addIt(add);
			add=0;
		}
	}
	inline bool Node::isRoot()const
	{	return p==null || (p->ch[0]!=this && p->ch[1]!=this);	}
	Node mem[MAXN<<1],*cur;
	inline Node* newNode()
	{
		Node* t=cur++;
		t->ch[0]=t->ch[1]=t->p=null;
		return t;
	}
	inline void rotate(Node* t)
	{
		Node* p=t->p;
		p->pushdown();t->pushdown();
		bool d=t->d();
		if(!p->isRoot()) p->p->setc(t,p->d());
		else t->p=p->p;
		p->setc(t->ch[d^1],d);
		t->setc(p,d^1);
	}
	void splay(Node* t)
	{
		t->pushdown();
		while(!t->isRoot())
		{
			if(t->p->isRoot()) rotate(t);
			else t->d()==t->p->d()?(rotate(t->p),rotate(t)):(rotate(t),rotate(t));
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
	void cut(Node* u) //cut u and its parent
	{
		access(u);
		splay(u);
		if(u->ch[0]==null) return;
		Node* f=u->ch[0];
		while(f->ch[1]!=null) f=f->ch[1];
		splay(f);
		f->setc(null,1);
		f->ch[1]->p=null;
	}
	void addToRoot(Node* u)
	{
		access(u);
		splay(u);
		u->ch[0]->addIt(1);
	}
	void init()
	{
		cur=mem;
		null=cur++;
	}
}

struct State{
	State* go[SIGMA_SIZE],*suf;
	LCT::Node *node;
	int val;
	State():val(0),suf(0) {memset(go,0,sizeof go);}
}*root,*last;
State stateMem[MAXN<<1],*cur;
State* newState()
{
	cur->node=LCT::newNode();
	return cur++;
}
void init()
{
	LCT::init();
	cur=stateMem;
	root=last=newState();
}
void extend(int w)
{
	State* p=last,*np=newState();
	np->val=p->val+1;
	LCT::Node* nd=np->node;
	nd->cnt=1;
	while(p && !p->go[w]) p->go[w]=np,p=p->suf;
	if(!p) np->suf=root,nd->p=root->node;
	else
	{
		State* q=p->go[w];
		if(q->val==p->val+1) np->suf=q,nd->p=q->node;
		else
		{
			State* nq=newState();
			nq->val=p->val+1;
			memcpy(nq->go,q->go,sizeof(q->go));
			LCT::cut(q->node);
			nq->suf=q->suf;
			nq->node->cnt=q->node->cnt;
			nq->node->p=q->suf->node;
			q->suf=np->suf=nq;
			q->node->p=nd->p=nq->node;
			while(p && p->go[w]==q) p->go[w]=nq,p=p->suf;
		}
	}
	LCT::addToRoot(nd);
	last=np;
}
void decodeWithMask(char *s,int len,int mask)
{
	for(int i=0;i<len;++i)
	{
		mask=(mask*131+i)%len;
		std::swap(s[i],s[mask]);
	}
}
int query(char* s,int len)
{
//	printf("%s\n",s);
	State* t=root;
	for(int i=0;i<len;++i)
	{
		int w=idx(s[i]);
		if(!t->go[w]) return 0;
		t=t->go[w];
	}
	LCT::splay(t->node);
	return t->node->cnt;
}
void insert(char* s,int len)
{
//	printf("%s\n",s);
	for(int i=0;i<len;++i)
		extend(idx(s[i]));
}
char cmd[10],s[MAXQ];
int main()
{
	init();
	int Q;
	scanf("%d",&Q);
	scanf("%s",s);
	insert(s,strlen(s));
	int mask=0;
	while(Q--)
	{
		scanf("%s%s",cmd,s);
		decodeWithMask(s,strlen(s),mask);
		if(cmd[0]=='Q')
		{
			int t=query(s,strlen(s));
			mask^=t;
			printf("%d\n",t);
		}
		else insert(s,strlen(s));
	}
	return 0;
}
