#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
using namespace std;
struct Node{
	int s,v,r;
	Node* ch[2];
	Node(int v):v(v) {ch[0]=ch[1]=NULL;s=1;r=rand();}
	int cmp(int x) const
	{
		if(v==x) return -1;
		return x<v?0:1;
	}
	void maintain()
	{
		s=1;
		if(ch[0]) s+=ch[0]->s;
		if(ch[1]) s+=ch[1]->s;
	}
}*root;

void rotate(Node* &o,int d)
{
	Node* k=o->ch[d^1];
	o->ch[d^1]=k->ch[d];
	k->ch[d]=o;
	o->maintain();
	k->maintain();
	o=k;
}

void insert(Node* &o,int x)
{
	if(!o) o=new Node(x);
	else
	{
		int d=o->cmp(x);
		if(d==-1) return;
		insert(o->ch[d],x);
		if(o->ch[d]->r > o->r) rotate(o,d^1);
	}
	o->maintain();
}

const int INF=1<<28;
int get_before(Node* o,int x)
{
	if(!o) return -INF;
	if(o->v <= x) return max(o->v,get_before(o->ch[1],x));
	else return get_before(o->ch[0],x);
}

int get_after(Node* o,int x)
{
	if(!o) return INF;
	if(o->v >= x) return min(o->v,get_after(o->ch[0],x));
	else return get_after(o->ch[1],x);
}

int query(int x)
{
	int ans1=x-get_before(root,x),ans2=get_after(root,x)-x;
	return ans1<ans2?ans1:ans2;
}

int main()
{
	freopen("1.in","r",stdin);
	srand(23333);
	int n;
	root=NULL;
	scanf("%d",&n);
	int t;
	scanf("%d",&t);
	insert(root,t);
	int ans=0;
	ans+=t;
	while(--n)
	{
		if(scanf("%d",&t)==EOF) t=0;
		ans+=query(t);
		insert(root,t);
	}
	printf("%d\n",ans);
	return 0;
}
