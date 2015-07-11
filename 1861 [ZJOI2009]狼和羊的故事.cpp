#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

struct Node{
	int s,v;
	Node* ch[2];
	int cmp(int k)
	{
		int d=k-ch[0]->s;
		if(d==1) return -1;
		return d<=0?0:1;
	}
	void maintain()
	{
		s=ch[0]->s + ch[1]->s +1;
	}
}*null;

void splay(Node* o,int k)
{
	int d=o->cmp(k);
	if(d==1) k-=o->ch[0]->s+1;
	if(d!=-1)
	{
		Node* p=o->ch[d];
		int d2=p->cmp(k);
		int k2=(d2==0?k:k-p->ch[0]->s-1);
		if(d2!=-1)
		{
			splay(p->ch[d2],k2);
			if(d==d2) rotate(o,d^1);
			else rotate(o->ch[d],d);
		}
		rotate(o,ch[d^1]);
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

void insert(Node* o,int k)
{
	int d=o->cmp(k);

}
struct splay_sequence{
	Node* root;
	int n;
	Node* build(int sz)
	{
		if(!sz) return null;
		Node* L=build(sz>>1);
		Node* o;
		o->v=++n;
		o->ch[0]=L;
		o->ch[1]=build(sz-(sz>>1)-1);
		o->maintain();
		return o;
	}
	void init(int sz)
	{
		n=0;
		null->s=0;
		root=build(sz);
	}
}ss;
