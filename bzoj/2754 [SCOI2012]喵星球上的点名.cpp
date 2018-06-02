#include<cstdio>
#include<cstring>
#include<map>
#include<vector>
const int MAXL=100000+5;
const int MAXN=20000+5;
const int MAXM=50000+5;
std::vector<int> name[MAXN];
typedef std::vector<int>::iterator it;
struct Trie{
	std::map<int,Trie*> ch;
	Trie *fail,*sufLink;
	std::vector<int> st;	//处理相同的点名串
	int id;
	static int numId;
	Trie()
	{
		ch.clear();
		fail=sufLink=0;
		id=numId++;
		st.clear();
	}
	Trie* getch(int w)
	{
		if(!ch.count(w)) ch[w]=new Trie;
		return ch[w];
	}
};
int Trie::numId=0;
Trie* root=new Trie;
void insert(std::vector<int>&a,int id)
{
	Trie* t=root;
	for(it i=a.begin();i!=a.end();++i)
		t=t->getch(*i);
	(t->st).push_back(id);
}
Trie* que[MAXL];
int qh,qt;
typedef std::map<int,Trie*>::iterator mit;
void build()
{
	qh=qt=0;
	que[qt++]=root;
	while(qh<qt)
	{
		Trie* u=que[qh++];
		for(mit i=(u->ch).begin();i!=(u->ch).end();++i)
		{
			Trie* p=u->fail;
			int t=i->first;Trie*&v=i->second;
			while(p && !p->ch[t]) p=p->fail;
			if(!p) v->fail=root;
			else v->fail=p->ch[t];
			if((v->fail->st).size()) v->sufLink=v->fail;
			else v->sufLink=v->fail->sufLink;
			que[qt++]=v;
		}
	}
}
int ans1[MAXM],ans2[MAXN];
bool vis[MAXL],mark[MAXM];
std::vector<int> t1,t2;
void count(Trie* u,int x)
{
	if(!u || u==root || vis[u->id]) return;
	vis[u->id]=1;
	t1.push_back(u->id);
	for(it i=(u->st).begin();i!=(u->st).end();++i) if(!mark[*i])
	{
		mark[*i]=1;t2.push_back(*i);
		ans1[*i]++;
		ans2[x]++;
	}
	count(u->sufLink,x);
}
int n,m;
void readString(std::vector<int>& a)
{
	int l,t;
	scanf("%d",&l);
	while(l--)
	{
		scanf("%d",&t);
		a.push_back(t);
	}
}
void input()
{
	scanf("%d%d",&n,&m);
	std::vector<int> a;
	for(int i=0;i<n;++i)
	{
		readString(name[i]);
		name[i].push_back(-1);
		readString(name[i]);
	}
	for(int i=0;i<m;++i)
		a.clear(),readString(a),insert(a,i+1);
}
void solve()
{
	input();
	build();
	for(int i=0;i<n;++i)
	{
		Trie* u=root;
		for(it j=name[i].begin();j!=name[i].end();++j)
		{
			while(u && !u->ch[*j]) u=u->fail;
			if(!u) u=root;
			else u=u->ch[*j];
			if(u->st.size()) count(u,i+1);
			else if(u->sufLink && u->sufLink!=root) count(u->sufLink,i+1);
		}
		for(it j=t1.begin();j!=t1.end();++j) vis[*j]=0;
		for(it j=t2.begin();j!=t2.end();++j) mark[*j]=0;
		t1.clear();t2.clear();
	}
	for(int i=1;i<=m;++i) printf("%d\n",ans1[i]);
	for(int i=1;i<=n;++i)
		printf("%d%c",ans2[i],i==n?'\n':' ');
}
int main()
{
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	solve();
	return 0;
}

