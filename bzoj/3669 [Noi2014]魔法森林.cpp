#include<cstdio>
#include<algorithm>
#define rep(i,n) for(int i=0;i<n;++i)
const int MAXN=50000+5;
const int MAXM=100000+5;
const int INF=~0U>>1;
struct Node{
    int mxv,v;
    Node* p,*ch[2],*mx;
    int e;
    bool rev;
    Node() {mxv=v=-1;}
    inline bool d() const
    {
        return p->ch[1]==this;
    }
    inline void revIt()
    {
        rev^=1;
        std::swap(ch[0],ch[1]);
    }
    inline void setc(Node* t,bool d)
    {
        ch[d]=t;
        t->p=this;
    }
    inline void maintain()
    {
        mxv=v;mx=this;
        rep(i,2) if(ch[i]->mxv>mxv)
        {
            mxv=ch[i]->mxv;
            mx=ch[i]->mx;
        }
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
inline void link(Node* u,Node* v)
{
    makeRoot(u);u->p=v;
}
inline void cut(Node* u,Node* v)
{
    makeRoot(u);
    access(v);
    splay(v);
    if(v->ch[0]==u)
    {
        v->setc(null,0);
        v->maintain();
        u->p=null;
    }
}
inline Node* find(Node* u)
{
    for(;u->p!=null;u=u->p);
    return u;
}
inline void change(Node* u,int v)
{
    access(u);
    splay(u);
    u->v=v;
    u->maintain();
}
inline void getMax(Node* u,Node* v,int& maxv,int& e,Node*& mx)
{
    makeRoot(u);
    access(v);
    splay(v);
    maxv=v->mxv;
    mx=v->mx;
    e=v->mx->e;
}
inline int query(Node* u,Node* v)
{
    makeRoot(u);
    access(v);
    splay(v);
    return v->mxv;
}
Node mem[MAXN+MAXM],*C=mem;
inline Node* newNode(int v,int e)
{
    C->p=C->ch[0]=C->ch[1]=null;
    C->rev=0;
    C->v=C->mxv=v;
    C->mx=C;
    C->e=e;
    return C++;
}
struct Edge{
    int u,v,a,b;
    Edge() {}
    Edge(int u,int v,int a,int b):u(u),v(v),a(a),b(b) {}
    bool operator<(const Edge& rhs) const
    {
        return a<rhs.a;
    }
}edges[MAXM];
Node* pt[MAXN+MAXM];
int n,m;
int ans=INF;
int main()
{
    //freopen("1.in","r",stdin);
    scanf("%d%d",&n,&m);
    rep(i,m)
    {
        int u,v,a,b;
        scanf("%d%d%d%d",&u,&v,&a,&b);
        edges[i]=Edge(u,v,a,b);
    }
    std::sort(edges,edges+m);
    rep(i,n) pt[i+1]=newNode(0,-1);
    rep(i,m) pt[i+n+1]=newNode(edges[i].b,i);
    rep(i,m)
    {
        Edge e=edges[i];
        if(find(pt[e.u])!=find(pt[e.v])) link(pt[e.u],pt[i+n+1]),link(pt[e.v],pt[i+n+1]);
        else
        {
            int en,maxv;
            Node* mx;
            getMax(pt[e.u],pt[e.v],maxv,en,mx);
            if(maxv>e.b)
            {
                cut(pt[edges[en].u],pt[en+n+1]);
                cut(pt[edges[en].v],pt[en+n+1]);
                link(pt[e.u],pt[i+n+1]);
                link(pt[e.v],pt[i+n+1]);
            }
        }
        if(find(pt[1])==find(pt[n])) ans=std::min(ans,query(pt[1],pt[n])+edges[i].a);
    }
    printf("%d\n",ans==INF?-1:ans);
    return 0;
}
