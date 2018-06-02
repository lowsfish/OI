#include<cstdio>
#include<algorithm>
const int MAXN=50000+10;
const int INF=~0U>>1;
struct Node{
    int s,v;
    int mx,add;
    bool rev;
    Node* p,*ch[2];
    Node() {s=add=0;v=mx=-INF;}
    inline void setc(Node* t,bool d)
    {
        ch[d]=t;
        t->p=this;
    }
    inline void maintain()
    {
        s=ch[0]->s+ch[1]->s+1;
        mx=std::max(v,std::max(ch[0]->mx,ch[1]->mx));
    }
    inline bool d()const
    {
        return p->ch[1]==this;
    }
    inline void revIt()
    {
        rev^=1;
        std::swap(ch[0],ch[1]);
    }
    inline void addIt(int ad)
    {
        add+=ad;
        mx+=ad;
        v+=ad;
    }
    inline void pushdown();
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
    if(add)
    {
        if(ch[0]!=null) ch[0]->addIt(add);
        if(ch[1]!=null) ch[1]->addIt(add);
        add=0;
    }
}
inline Node* newNode(int v)
{
    C->v=C->mx=v;
    C->p=C->ch[0]=C->ch[1]=null;
    C->rev=C->add=0;
    C->s=1;
    return C++;
}
Node* build(int l,int r)
{
    if(l>=r) return null;
    Node* t=newNode(0);
    int m=(l+r)>>1;
    Node* L=build(l,m),*R=build(m+1,r);
    t->setc(L,0);t->setc(R,1);
    t->maintain();
    return t;
}
Node* root;
inline void rot(Node* t)
{
    Node* p=t->p;
    p->pushdown();t->pushdown();
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
        if(t->p->p==f) rot(t);
        else t->d()==t->p->d()?(rot(t->p),rot(t)):(rot(t),rot(t));
    }
    t->maintain();
}
inline Node* select(int k)
{
    for(Node* t=root;;)
    {
        t->pushdown();
        int s=t->ch[0]->s;
        if(s==k) return t;
        if(k>s) k-=s+1,t=t->ch[1];
        else t=t->ch[0];
    }
}
inline void splay(int k,Node *f=null)
{
    splay(select(k),f);
}
inline Node*& get(int l,int r)  //[l,r)
{
    splay(l-1);
    splay(r,root);
    return root->ch[1]->ch[0];
}
int n,m;
int main()
{
    //freopen("1.in","r",stdin);
    scanf("%d%d",&n,&m);
    root=build(0,n+2);
    while(m--)
    {
        int k,l,r,v;
        scanf("%d%d%d",&k,&l,&r);
        Node*& t=get(l,r+1);
        if(k==1)
        {
            scanf("%d",&v);
            t->addIt(v);
        }
        else if(k==2)
            t->revIt();
        else
            printf("%d\n",t->mx);
    }
    return 0;
}
