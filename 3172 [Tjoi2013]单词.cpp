#include<cstdio>
#include<cstring>
const int MAXL=1000000+5;
const int MAXN=200+5;
const int SIGMA_SIZE=26;
inline int idx(char c)
{
	return c-'a';
}
struct Trie{
	Trie* ch[SIGMA_SIZE],*fail,*sufLink;
	int sum;
	int id;
	static int numId;
	Trie()
	{
		memset(ch,0,sizeof ch);
		fail=sufLink=0;
		id=numId++;
		sum=0;
	}
	Trie* getch(char c)
	{
		int w=idx(c);
		if(!ch[w]) ch[w]=new Trie;
		return ch[w];
	}
};
int Trie::numId=0;
Trie* root=new Trie;
int n;
char s[MAXL];
Trie* pos[MAXN];
void insert(char* s,int id)
{
	Trie* t=root;
	int len=strlen(s);
	for(int i=0;i<len;++i)
		t=t->getch(s[i]),t->sum++;
	pos[id]=t;
}
void input()
{
	scanf("%d",&n);
	for(int i=0;i<n;++i)
	{
		scanf("%s",s);
		insert(s,i);
	}
}
Trie* que[MAXL];
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
			while(p && !p->ch[i]) p=p->fail;
			if(!p) v->fail=root;
			else v->fail=p->ch[i];
			que[qt++]=v;
		}
	}
	for(int i=qt-1;i>=0;--i)
	{
		Trie* u=que[i];
		if(u->fail) u->fail->sum+=u->sum;
	}
}
int main()
{
//	freopen("1.in","r",stdin);
	input();
	build();
	for(int i=0;i<n;++i) printf("%d\n",pos[i]->sum);
	return 0;
}
