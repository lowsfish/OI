#include<cstdio>
#include<algorithm>
const int MAXN=10000+5;
const int INF=~0U>>1;
const int BUFFER_SIZE=10000;
const int MAXM=10000+5;
struct Tree{
	Tree* pl,*pr;
	int l,r,sum;
	Tree* set(int _l,int _r,Tree* _pl,Tree* _pr)
	{
		l=_l;r=_r;pl=_pl;pr=_pr;
		sum=pl->sum+pr->sum;
		return this;
	}
	Tree* set(int _l,int _r,int all);
	Tree* add(int pos,int ad);
};
Tree* buffer=0,*cur;
inline Tree* get()
{
	if(!buffer || cur-buffer==BUFFER_SIZE)
		buffer=new Tree[BUFFER_SIZE],cur=buffer;
	return cur++;
}
Tree* Tree::set(int _l,int _r,int all)
{
	l=_l;r=_r;
	if(l+1==r) sum=all;
	else
	{
		int m=(l+r)>>1;
		pl=get()->set(l,m,all);
		pr=get()->set(m,r,all);
		sum=pl->sum+pr->sum;
	}
	return this;
}
Tree* Tree::add(int pos,int ad)
{
	if(l+1==r) return get()->set(l,r,sum+ad);
	int m=(l+r)>>1;
	if(pos<m) return get()->set(l,r,pl->add(pos,ad),pr);
	else return get()->set(l,r,pl,pr->add(pos,ad));
}
inline int lowbit(int x)
{	return x&-x;	}
int n,m;
Tree* root[MAXN];
void update(int x,int pos,int ad)
{
	for(;x<=n;x+=lowbit(x))
		root[x]=root[x]->add(pos,ad);
}
Tree* ptl[MAXN],*ptr[MAXN];
int lnum,rnum;
inline void get_trees(int x,int y)
{
	lnum=rnum=0;
	for(;x>0;x-=lowbit(x))
		ptl[lnum++]=root[x];
	for(;y>0;y-=lowbit(y))
		ptr[rnum++]=root[y];
}
inline int get_sum()
{
	int cnt1=0,cnt2=0;
	for(int i=0;i<lnum;++i) cnt1+=ptl[i]->pl->sum;
	for(int i=0;i<rnum;++i) cnt2+=ptr[i]->pl->sum;
	return cnt2-cnt1;
}
inline int query(int x,int y,int k)
{
	get_trees(x-1,y);
	while(ptr[0]->l +1 < ptr[0]->r)
	{
		int cnt=get_sum();
		if(cnt<=k)
		{
			k-=cnt;
			for(int i=0;i<lnum;++i) ptl[i]=ptl[i]->pr;
			for(int i=0;i<rnum;++i) ptr[i]=ptr[i]->pr;
		}
		else
		{
			for(int i=0;i<lnum;++i) ptl[i]=ptl[i]->pl;
			for(int i=0;i<rnum;++i) ptr[i]=ptr[i]->pl;
		}
	}
	return ptr[0]->l;
}
struct Ask{
	int kind,a,b,c;
}ask[MAXM];
int w[MAXN],sortw[MAXN+MAXM];
int main()
{
	freopen("1.in","r",stdin);
	scanf("%d%d",&n,&m);
	int p;
	for(int i=0;i<n;++i)
		scanf("%d",w+i),sortw[i]=w[i];
	p=n;
	char cmd[5];
	for(int i=0;i<m;++i)
	{
		scanf("%s",cmd);
		if(cmd[0]=='Q')
		{
			ask[i].kind=0;
			scanf("%d%d%d",&ask[i].a,&ask[i].b,&ask[i].c);
		}
		else
		{
			ask[i].kind=1;
			scanf("%d%d",&ask[i].a,&ask[i].b);
			sortw[p]=ask[i].b;
			p++;
		}
	}
	std::sort(sortw,sortw+p);
	int nn=std::unique(sortw,sortw+p)-sortw;
	for(int i=0;i<n;++i) w[i]=std::lower_bound(sortw,sortw+nn,w[i])-sortw;
	root[0]=get()->set(0,nn,0);
	for(int i=1;i<=n;++i) root[i]=root[0]->add(w[i-1],1);
	for(int i=1;i<=n;++i) update(i+lowbit(i),w[i-1],1);
	for(int i=0;i<m;++i)
	{
		if(!ask[i].kind) printf("%d\n",sortw[query(ask[i].a,ask[i].b,ask[i].c-1)]);
		else
		{
			int t=std::lower_bound(sortw,sortw+nn,ask[i].b)-sortw;
			update(ask[i].a,w[ask[i].a-1],-1);
			w[ask[i].a-1]=t;
			update(ask[i].a,t,1);
		}
	}
	return 0;
}
