#include<cstdio>
#include<algorithm>
#include<cstdlib>
const int MAXN=100000+5;
const int INF=~0U>>1;
struct Node{
	int s,v;
	Node* p,*ch[2];
	Node() {s=v=0;}
	inline bool d()const
	{
		return p->ch[1]==this;
	}
	inline void maintain()
	{
		s=ch[0]->s+ch[1]->s+1;
	}
	inline void setc(Node* t,bool d)
	{
		ch[d]=t;
		t->p=this;
	}
}Tnull,*null=&Tnull,*root;
Node mem[MAXN],*C;
inline Node* newNode(int v)
{
	C->v=v;
	C->s=1;
	C->p=C->ch[0]=C->ch[1]=null;
	return C++;
}
inline void init()
{
	C=mem;
	root=newNode(0);
	root->setc(newNode(0),1);
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
		if(k==s) return t;
		if(k>s) k-=s+1,t=t->ch[1];
		else t=t->ch[0];
	}
}
inline void splay(int k,Node* f=null)
{
	splay(select(k),f);
}
inline void insert(int p,int x)	
{
	splay(p);splay(p+1,root);
	root->ch[1]->setc(newNode(x),0);
	root->ch[1]->maintain();
	root->maintain();
}
int n,a[MAXN];
int now=0;
void get_sequence(Node* t)
{
	if(t==null) return;
	get_sequence(t->ch[0]);
	a[now++]=t->v;
	get_sequence(t->ch[1]);
}
int d[MAXN],g[MAXN];
void LIS()
{
	std::fill(g+1,g+n+1,INF);
	for(int i=1;i<=n;++i)
	{
		int k=std::lower_bound(g+1,g+n+1,a[i])-g;
		g[k]=a[i];
		d[a[i]]=k;
	}
}
int main()
{
	freopen("1.in","r",stdin);
	init();
	scanf("%d",&n);
	for(int i=1;i<=n;++i)
	{
		int x;
		scanf("%d",&x);
		insert(x,i);
	}
	get_sequence(root);
	LIS();
	int ans=0;
	for(int i=1;i<=n;++i) printf("%d\n",ans=std::max(ans,d[i]));
	return 0;
}
