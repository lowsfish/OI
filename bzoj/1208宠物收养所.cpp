#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
using namespace std;
typedef long long LL;
struct Node{
	LL v,r;
	Node* ch[2];
	Node(int v):v(v) {ch[0]=ch[1]=NULL;r=rand();}
	int cmp(LL x)
	{
		if(v==x) return -1;
		return x<v?0:1;
	}
}*pet,*people;

void rotate(Node* &o,int d)
{
	Node* k=o->ch[d^1];
	o->ch[d^1]=k->ch[d];
	k->ch[d]=o;
	o=k;
}

void insert(Node* &o,LL x)
{
	if(o==NULL) o=new Node(x);
	else
	{
		int d=o->cmp(x);
		if(d==-1) return;
		insert(o->ch[d],x);
		if(o->ch[d]->r > o->r) rotate(o,d^1);
	}
}

void remove(Node* &o,int x)
{
	int d=o->cmp(x);
	if(d==-1)
	{
		if(o->ch[0] && o->ch[1])
		{
			int d2=o->ch[0]->r > o->ch[1]->r?1:0;
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
}

const LL INF=((LL)1)<<40;
LL before(Node* o,LL x)
{
	if(!o) return -INF;
	if(o->v <= x) return max(o->v,before(o->ch[1],x));
	else return before(o->ch[0],x);
}

LL after(Node* o,LL x)
{
	if(!o) return INF;
	if(o->v >= x) return min(o->v,after(o->ch[0],x));
	else return after(o->ch[1],x);
}

const int MOD=1000000;
LL ans=0;
void work(int type,LL x)
{
	if(!type)
	{
		if(!people)
		{
			insert(pet,x);
			return;
		}
		LL ans1=before(people,x),ans2=after(people,x);
		if(x-ans1 <= ans2-x)
		{
			remove(people,ans1);
			ans+=x-ans1;
			ans%=MOD;
		}
		else
		{
			remove(people,ans2);
			ans+=ans2-x;
			ans%=MOD;
		}

	}
	else
	{
		if(!pet)
		{
			insert(people,x);
			return;
		}
		LL ans1=before(pet,x),ans2=after(pet,x);
		if(x-ans1 <= ans2-x)
		{
			remove(pet,ans1);
			ans+=x-ans1;
			ans%=MOD;
		}
		else
		{
			remove(pet,ans2);
			ans+=ans2-x;
			ans%=MOD;
		}
	}
}
int main()
{
	freopen("1.in","r",stdin);
	ios::sync_with_stdio(false);
	srand(23333);
	int n;
	cin>>n;
	while(n--)
	{
		int type;
		LL t;
		cin>>type>>t;
		work(type,t);
	}
	cout<<ans<<endl;
	return 0;
}
