#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;
const int INF=1<<28;
struct Node{
	int s,v,r,w;		//w代表重复值域
	Node* ch[2];
	Node(int v):v(v) {ch[0]=ch[1]=NULL;s=w=1;r=rand();}
	bool operator<(const Node& rhs)
	{
		return r<rhs.r;
	}
	int cmp(int x)
	{
		if(v==x) return -1;
		return x<v?0:1;
	}
	void maintain()
	{
		s=1;
		if(ch[0]!=NULL) s+=ch[0]->s;
		if(ch[1]!=NULL) s+=ch[1]->s;
		s+=w-1;
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
	if(o==NULL) o=new Node(x);
	else
	{
		int d=o->cmp(x);
		if(d==-1) ++(o->w),++(o->s);
		else
		{
			insert(o->ch[d],x);
			if(o->ch[d]->r > o->r) rotate(o,d^1);
		}
	}
	o->maintain();
}
void print(Node* o)
{
	if(!o) return;
	print(o->ch[0]);
	for(int i=0;i<o->w;++i) printf("%d\n",o->v);
	print(o->ch[1]);
}
int n;
int main()
{
	srand(23333);
	scanf("%d",&n);
	root=NULL;
	for(int i=0;i<n;++i) {int t;scanf("%d",&t);insert(root,t);}
	print(root);
	return 0;
}
