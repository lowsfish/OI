#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;
struct Node{
	Node* ch[2];
	int s,v;
	bool flip;
	int cmp(int k) const
	{
		int d=k-ch[0]->s;
		if(d==1) return -1;
		return d<=0?0:1;
	}
	void maintain()
	{
		s=ch[0]->s + ch[1]->s +1;
	}
	void pushdown()
	{
		if(!flip) return;
		flip=0;
		swap(ch[1],ch[0]);
		ch[1]->flip^=1;
		ch[0]->flip^=1;
	}
};

Node* null=new Node();
void rotate(Node* &o,int d)
{
	Node* k=o->ch[d^1];
	o->ch[d^1]=k->ch[d];
	k->ch[d]=o;
	o->maintain();
	k->maintain();
	o=k;
}
void splay(Node* &o,int k)
{
	o->pushdown();
	int d=o->cmp(k);
	if(d==1) k-=o->ch[0]->s+1;
	if(d!=-1)
	{
		Node* p=o->ch[d];
		p->pushdown();
		int d2=p->cmp(k);
		int k2=(d2==0?k:k-p->ch[0]->s-1);
		if(d2!=-1)
		{
			splay(p->ch[d2],k2);
			if(d==d2) rotate(o,d^1);
			else rotate(o->ch[d],d);
		}
		rotate(o,d^1);
	}
}

Node* merge(Node* left,Node* right)
{
	splay(left,left->s);
	left->ch[1]=right;
	left->maintain();
	return left;
}

void split(Node* o,int k,Node* &left,Node* &right)
{
	splay(o,k);
	left=o;
	right=o->ch[1];
	o->ch[1]=null;
	left->maintain();
}
struct splay_sequence{
	Node *root;
	int n;
	Node* build(int sz)
	{
		if(!sz) return null;
		Node* L=build(sz>>1);
		Node* o=new Node();
		o->v=++n;
		o->ch[0]=L;
		o->ch[1]=build(sz-(sz>>1)-1);
		o->flip=o->s=0;
		o->maintain();
		return o;
	}
	void init(int sz) {
		null->s=0;
		n=0;
		root=build(sz);
	}
}ss;
void print(Node*) ;
void flip(Node* &o,int a,int b)
{
	Node* left,*mid,*right,*p;
	split(o,a,left,p);
	split(p,b-a+1,mid,right);
	mid->flip^=1;
	o=merge(merge(left,mid),right);
}

void cut(Node* &o,int a,int b,int c)
{
	Node* left,*mid,*right,*p;
	split(o,a,left,p);
	split(p,b-a+1,mid,right);
	o=merge(left,right);
	split(o,c+1,left,right);
	o=merge(merge(left,mid),right);
}

vector<int> ans;
void print(Node* o)
{
	if(o==null) return;
	o->pushdown();
	print(o->ch[0]);
	ans.push_back(o->v);
	//printf("%d ",o->v);
	print(o->ch[1]);
}
int main()
{
	freopen("1.in","r",stdin);
	char s[50];
	int n,m;
	while(scanf("%d%d",&n,&m)!=EOF)
	{
		if(n<0) return 0;
		ss.init(n+1);
		while(m--)
		{
			scanf("%s",s);
			if(s[0]=='C')
			{
				int a,b,c;
				scanf("%d%d%d",&a,&b,&c);
				cut(ss.root,a,b,c);
			}
			else
			{
				int a,b;
				scanf("%d%d",&a,&b);
				flip(ss.root,a,b);
			}
		}
		ans.clear();
		print(ss.root);
		for(int i=1;i<ans.size();++i)
		{
			if(i!=1) putchar(' ');
			printf("%d",ans[i]-1);
		}
		putchar(10);
	}
	return 0;
}
