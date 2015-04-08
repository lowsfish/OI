#include<cstdio>
#include<cmath>
#include<cstring>
#include<cctype>
const int MAXL=20+5;
const int MAXN=100+5;
const int MAXK=20+5;
const int SIGMA_SIZE=70;
inline int idx(char c)
{
	if(isdigit(c)) return c-'0';
	if(isupper(c)) return c-'A'+10;
	return c-'a'+10+26;
}
int numId;
struct Trie{
	Trie* ch[SIGMA_SIZE],*fail;
	bool hasWord;
	int id;
	Trie()
	{
		memset(ch,0,sizeof ch);
		id=numId++;
		hasWord=0;
		fail=0;
	}
	Trie* getch(char c);
}mem[MAXL*MAXK],*C;
Trie* Trie::getch(char c)
{
	int w=idx(c);
	if(ch[w]==NULL) *C=Trie(),ch[w]=C++;
	return ch[w];
}
Trie* root;
int k,n,l;
double prob[SIGMA_SIZE];
bool have[SIGMA_SIZE];
bool vis[MAXK*MAXL][MAXN];
void input()
{
	memset(have,0,sizeof have);
	memset(vis,0,sizeof vis);
	numId=0;
	C=mem;
	mem[0]=Trie();
	root=C++;
	char s[MAXL];
	scanf("%d",&k);
	for(int i=0;i<k;++i)
	{
		scanf("%s",s);
		int len=strlen(s);
		Trie* t=root;
		for(int j=0;j<len;++j)
			t=t->getch(s[j]);
		t->hasWord=1;
	}
	double t;
	scanf("%d",&n);
	while(n--)
	{
		scanf("%s%lf",s,&t);
		prob[idx(s[0])]=t;
		have[idx(s[0])]=1;
	}
	scanf("%d",&l);
}
Trie* que[MAXL*MAXK];
int qh,qt;
void build()
{
	qh=qt=0;
	que[qt++]=root;
	while(qh<qt)
	{
		Trie* u=que[qh++];
		for(int i=0;i<SIGMA_SIZE;++i) if(u->ch[i])
		{
			Trie* v=u->ch[i];
			Trie* p=u->fail;
			if(!p) v->fail=root;
			else v->fail=p->ch[i];
			v->hasWord|=v->fail->hasWord;
			que[qt++]=v;
		}
		else if(u->fail) u->ch[i]=u->fail->ch[i];
		else u->ch[i]=root;
	}
}
typedef long long LL;
double dp[MAXK*MAXL][MAXN];
double src(Trie* u,int len)
{
	if(len==0) return 1.0;
	if(vis[u->id][len]) return dp[u->id][len];
	vis[u->id][len]=1;
	double&ans=dp[u->id][len];
	ans=0;
	for(int i=0;i<SIGMA_SIZE;++i)
	{
		Trie* v=u->ch[i];
		if(!v->hasWord && have[i]) ans+=prob[i]*src(v,len-1);
	}
	return ans;
}
const double eps=1e-10;
int main()
{
//	freopen("1.in","r",stdin);
	int T;
	scanf("%d",&T);
	for(int kase=1;kase<=T;++kase)
	{
		input();
		build();
		printf("Case #%d: %.6f\n",kase,src(root,l));
	}
	return 0;
}
