#include<cstdio>
#include<cstring>
#include<algorithm>
const int MAXN=250000+5;
const int SIGMA_SIZE=26;
inline int idx(char c)
{
	return c-'a';
}
struct State{
	int val,sum;
	State* suf,*go[SIGMA_SIZE];
	State():val(0),sum(0),suf(0) {memset(go,0,sizeof go);}
}*root,*last;
State mem[MAXN<<1],*cur;
inline void init()
{
	cur=mem;
	root=last=cur++;
}
inline void extend(int w)
{
	State* p=last,*np=cur++;
	np->val=p->val+1;
	while(p && !p->go[w]) p->go[w]=np,p=p->suf;
	if(!p) np->suf=root;
	else
	{
		State* q=p->go[w];
		if(q->val == p->val+1) np->suf=q;
		else
		{
			State* nq=cur++;
			memcpy(nq->go,q->go,sizeof q->go);
			nq->val=p->val+1;
			nq->suf=q->suf;
			np->suf=q->suf=nq;
			while(p && p->go[w]==q) p->go[w]=nq,p=p->suf;
		}
	}
	last=np;
}
char s[MAXN];
int n;
void input()
{
	scanf("%s",s);
	n=strlen(s);
	for(int i=0;i<n;++i) extend(idx(s[i]));
}
State* pt[MAXN<<1];
int ans[MAXN];
void work()
{
	static int ws[MAXN<<1];
	for(int i=0;i<cur-mem;++i) ws[i]=0;
	for(State* t=mem+1;t!=cur;++t) ++ws[t->val];
	for(int i=0;i<cur-mem-1;++i) ws[i+1]+=ws[i];
	for(State* t=cur-1;t!=mem;--t) pt[--ws[t->val]]=t;
	State* t=root;
	for(int i=0;i<n;++i) t=t->go[idx(s[i])],++t->sum;
	for(int i=cur-mem-2;i>=0;--i)
	{
		State* u=pt[i];
		ans[u->val]=std::max(ans[u->val],u->sum);
		if(u->suf) u->suf->sum+=u->sum;
	}
	for(int i=1;i<=n;++i) printf("%d\n",ans[i]);
}
int main()
{
	//freopen("1.in","r",stdin);
	init();
	input();
	work();
	return 0;
}
