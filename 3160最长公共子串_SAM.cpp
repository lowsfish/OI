#include<cstdio>
#include<cstring>
#include<algorithm>
#define rep(i,n) for(int i=0;i<n;++i)
const int MAXN=100000+5;
const int INF=~0U>>1;
const int MAXM=26;
struct State{
	int val;
	State* suf,*go[MAXM];
	State():suf(0),val(0) {memset(go,0,sizeof(go));}
}*root,*last;
State mem[MAXN<<1],*C;
inline void init()
{
	C=mem;
	last=root=C++;
}
inline void extend(int w)
{
	State* p=last,*np=C++;
	*np=State();np->val=p->val+1;
	while(p && !p->go[w]) p->go[w]=np,p=p->suf;
	if(!p) np->suf=root;
	else
	{
		State* q=p->go[w];
		if(q->val==p->val+1) np->suf=q;
		else
		{
			State* nq=C++;
			memcpy(nq->go,q->go,sizeof(q->go));
			nq->suf=q->suf;
			nq->val=p->val+1;
			q->suf=np->suf=nq;
			while(p && p->go[w]==q) p->go[w]=nq,p=p->suf;
		}
	}
	last=np;
}
char s1[MAXN],s2[MAXN];
int n1,n2;
int main()
{
	init();
	scanf("%s%s",s1,s2);
	n1=strlen(s1),n2=strlen(s2);
	rep(i,n1) extend(s1[i]-'a');
	State* t=root;
	int tmp=0,ans=0;
	rep(i,n2)
	{
		int d=s2[i]-'a';
		if(t->go[d]) t=t->go[d],tmp++;
		else
		{
			while(t && !t->go[d]) t=t->suf;
			if(!t) t=root,tmp=0;
			else tmp=t->val+1,t=t->go[d];
		}
		ans=std::max(ans,tmp);
	}
	printf("%d\n",ans);
	return 0;
}
