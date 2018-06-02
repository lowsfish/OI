#include<cstdio>
#include<algorithm>
const int MAXN=1000000+10;
const int INF=~0U>>1;
int a[MAXN];
struct Node{
    int s,v;
    int lmax,rmax,mmax,sum;
    bool rev,same;
    Node* p,*ch[2];
    Node() {same=sum=s=v=rev=0;lmax=rmax=mmax=-INF;}
    inline void maintain()
    {
        s=ch[0]->s+ch[1]->s+1;
        sum=v+ch[0]->sum+ch[1]->sum;
        lmax=std::max(ch[0]->lmax,ch[0]->sum+v+std::max(0,ch[1]->lmax));
        rmax=std::max(ch[1]->rmax,ch[1]->sum+v+std::max(0,ch[0]->rmax));
        mmax=std::max(std::max(ch[0]->mmax,ch[1]->mmax),std::max(0,ch[0]->rmax)+v+std::max(0,ch[1]->lmax));
    }
    inline void setc(Node* t,bool d)
    {
        ch[d]=t;
        t->p=this;
    }
    inline void MakeSame(int sv)
    {
        v=sv;
        same=1;
        sum=s*sv;
        mmax=rmax=lmax=std::max(v,sum);
    }
    inline void revIt()
    {
        std::swap(ch[0],ch[1]);
        std::swap(lmax,rmax);
        rev^=1;
    }
    inline bool d() {return p->ch[1]==this;}
    inline void pushdown();
}Tnull,*null=&Tnull;
inline void Node::pushdown()
{
    if(rev)
    {
        if(ch[0]!=null) ch[0]->revIt();
        if(ch[1]!=null) ch[1]->revIt();
        rev=0;
    }
    if(same)
    {
        if(ch[0]!=null) ch[0]->MakeSame(v);
        if(ch[1]!=null) ch[1]->MakeSame(v);
        same=0;
    }
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
    if(p==root)
        root=t;
}
void splay(Node* t,Node* f=null)
{
    while(t->p!=f)
    {
        if(t->p->p==f) rot(t);
        else t->d()==t->p->d()?(rot(t->p),rot(t)):(rot(t),rot(t));
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
inline Node*& get(int l,int r) //[l,r)
{
    Node* L=select(l-1);
    Node* R=select(r);
    splay(L);
    splay(R,L);
    return R->ch[0];
}
void DeleteTree(Node*& t)
{
    if(t==null) return;
    DeleteTree(t->ch[0]);
    DeleteTree(t->ch[1]);
    delete t;
    t=null;
}
Node* build(int l,int r) //[l,r)
{
    if(l>=r) return null;
    int m=l+r>>1;
    Node* t=new Node();
    Node* L=build(l,m),*R=build(m+1,r);
    t->v=t->sum=t->lmax=t->rmax=t->mmax=a[m];
    t->setc(L,0);
    t->setc(R,1);
    t->maintain();
    return t;
}
void Insert(int pos,int tot)
{
    if(!tot) return;
    for(int i=0;i<tot;++i) scanf("%d",a+i);
    Node* t=build(0,tot);
    splay(select(pos));
    splay(select(pos+1),root);
    root->ch[1]->setc(t,0);
    root->ch[1]->maintain();
    root->maintain();
}
inline void Delete(int pos,int tot)
{
    if(!tot) return;
    Node*& t=get(pos,pos+tot);
    DeleteTree(t);
    root->ch[1]->maintain();
    root->maintain();
}
inline void MakeSame(int pos,int tot,int c)
{
    if(!tot) return;
    Node*& t=get(pos,pos+tot);
    t->MakeSame(c); 
    t->p->maintain();
    t->p->p->maintain();
}
inline void Reverse(int pos,int tot)
{
    if(!tot || tot==1) return;
    Node*& t=get(pos,pos+tot);
    t->revIt();
    t->p->maintain();
    t->p->p->maintain();
}
inline int GetSum(int pos,int tot)
{
    if(!tot) return 0;
    Node*& t=get(pos,pos+tot);
    return t->sum;
}
inline int MaxSum()
{
    Node*& t=get(1,root->s-1);
    return t->mmax;
}
int n,m;
char s[20];
int main()
{
    //freopen("sequence.in","r",stdin);
    //freopen("sequence.out","w",stdout);
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i) scanf("%d",a+i);
    root=build(0,n+2);
    root->p=null;
    while(m--)
    {
        int pos,tot,c;
        scanf("%s",s);
        if(s[2]!='X') scanf("%d%d",&pos,&tot);
        if(s[2]=='K') scanf("%d",&c);
        switch(s[2])
        {
            case 'T':printf("%d\n",GetSum(pos,tot));
                     break;
            case 'S':Insert(pos,tot);
                     break;
            case 'V':Reverse(pos,tot);
                     break;
            case 'L':Delete(pos,tot);
                     break;
            case 'X':printf("%d\n",MaxSum());
                     break;
            case 'K':MakeSame(pos,tot,c);
                     break;
        }
    }
    return 0;
}
