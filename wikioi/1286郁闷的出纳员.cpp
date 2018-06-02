#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<ctime>
#include<algorithm>
#include<queue>
using namespace std;
int n,minm,del=0,ans=0;
struct Node{
	int s,v,r;
	Node *ch[2];
	Node(int v):v(v) {s=1;ch[0]=ch[1]=NULL;r=rand();}
	bool operator < (const Node& rhs)const
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
	}
}*root;

void rotate(Node* &o,int d)
{
	Node *k=o->ch[d^1];
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
		int d=(x<o->v?0:1);
		insert(o->ch[d],x);
		if(o->ch[d]->r > o->r) rotate(o,d^1);
	}
	o->maintain();
}

void remove(Node* &o,int x)
{
	int d=o->cmp(x);
	if(d==-1)
	{
		if(o->ch[0]!=NULL && o->ch[1]!=NULL)
		{
			int d2=(o->ch[0]->r > o->ch[1]->r?1:0);
			rotate(o,d2);
			remove(o->ch[d2],x);
		}
		else
		{
			if(o->ch[0]==NULL) o=o->ch[1];
			else o=o->ch[0];
		}
	}
	else remove(o->ch[d],x);
	if(o!=NULL) o->maintain();
}

int kth(Node* o,int k)
{
	if(k<=0 || o==NULL || k>o->s) return -1;
	int s=(o->ch[1]==NULL?0:o->ch[1]->s);
	if(k==s+1) return o->v;
	else if(k<=s) return kth(o->ch[1],k);
	else return kth(o->ch[0],k-s-1);
}

void remove_tree(Node* &o)
{
	if(o==NULL) return;
	remove_tree(o->ch[0]);
	remove_tree(o->ch[1]);
	delete o;
	o=NULL;
}

int Delete(Node* &o)
{
	int res=0;
	if(o==NULL) return 0;
	if(o->v + del <minm)
	{
		if(o->ch[0]!=NULL)res+=o->ch[0]->s+1;
		else res+=1;
		remove_tree(o->ch[0]);
		o=o->ch[1];
		res+=Delete(o);
	}
	else
	{
		res+=Delete(o->ch[0]);
		if(o)o->maintain();
	}
	if(o)o->maintain();
	return res;
}
int main()
{
	//freopen("1.in","r",stdin);
	srand((int)time(NULL));
	char s[2];
	int k;
	scanf("%d%d",&n,&minm);
	root=NULL;
	while(n--)
	{
		scanf("%s%d",s,&k);
		if(s[0]=='I')
		{
			if(k>=minm) insert(root,k-del);
		}
		else if(s[0]=='A') del+=k;
		else if(s[0]=='S')
		{
			del-=k;
			ans+=Delete(root);
		}
		else
		{
			if(!root || root->s < k) printf("-1\n");
			else printf("%d\n",kth(root,k)+del);
		}
	}
	printf("%d\n",ans);
	return 0;
}
