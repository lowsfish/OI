#include<cstdio>
#include<cstring>
#include<algorithm>
const int MAXL=30000+5;
const int SIGMA_SIZE=2;
inline int idx(char c)
{	return c-'0';	}
struct Trie{
	Trie *ch[SIGMA_SIZE],*fail;
	bool hasWord;
	int id;
	static int numId;
	Trie()
	{
		memset(ch,0,sizeof ch);
		fail=0;
		hasWord=0;
		id=numId++;
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
inline void ins(char *s)
{
	int len=strlen(s);
	Trie* t=root;
	for(int i=0;i<len;++i)
		t=t->getch(s[i]);
	t->hasWord=1;
}
char s[MAXL];
void input()
{
	scanf("%d",&n);
	for(int i=0;i<n;++i)
	{
		Trie* t=root;
		scanf("%s",s);
		ins(s);
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
			if(!p) v->fail=root;
			else v->fail=p->ch[i];
			v->hasWord|=v->fail->hasWord;
			que[qt++]=v;
		}
		else if(u->fail) u->ch[i]=u->fail->ch[i];
		else u->ch[i]=root;
	}
}
bool inStack[MAXL],vis[MAXL];
bool dfs(Trie* u)
{
	inStack[u->id]=1;
	for(int i=0;i<SIGMA_SIZE;++i)
	{
		Trie* v=u->ch[i];
		if(inStack[v->id]) return 1;
		if(vis[v->id] || v->hasWord) continue;
		vis[v->id]=1;
		if(dfs(v)) return 1;
	}
	inStack[u->id]=0;
	return 0;
}
int main()
{
	//freopen("1.in","r",stdin);
	input();
	build();
	printf("%s\n",dfs(root)?"TAK":"NIE");
	return 0;
}

