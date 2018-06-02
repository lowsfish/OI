#include<cstdio>
#include<algorithm>
#include<vector>
#include<iostream>
const int MAXN=100000+10;
std::vector<int> sons[MAXN];
typedef long long LL;
int L[MAXN],C[MAXN],M;
LL ans=0;
inline LL max(LL a,LL b)
{
	return a<b?b:a;
}
struct Node{
	Node* ch[2];
	int v,dist;
	Node(int v=0):v(v),dist(0) {ch[0]=ch[1]=NULL;}
};
struct HSJ{
	Node* o;
	LL sum,cnt;
	HSJ(Node* o,LL sum,LL cnt):o(o),sum(sum),cnt(cnt) {}
};
Node* merge(Node* A,Node* B)
{
	if(A==NULL) return B;
	if(B==NULL) return A;
	if(A->v < B->v) std::swap(A,B);
	A->ch[1]=merge(A->ch[1],B);
	if(!A->ch[0] || A->ch[0]->dist < A->ch[1]->dist) std::swap(A->ch[0],A->ch[1]);
	if(!A->ch[1]) A->dist=0;
	else A->dist=A->ch[1]->dist+1;
	return A;
}
void delmax(Node* &o)
{
	o=merge(o->ch[0],o->ch[1]);
}
HSJ src(int u)
{
	if(sons[u].empty())
	{
		if(C[u]>M) return HSJ(NULL,0,0);
		else 
		{
			Node* k=new Node(C[u]);
			ans=max(ans,L[u]);
			return HSJ(k,C[u],1);
		}
	}
	LL sum=C[u],cnt=1;
	Node* o=new Node(C[u]);
	for(int i=0;i<sons[u].size();++i)
	{
		HSJ k=src(sons[u][i]);
		o=merge(o,k.o);
		sum+=k.sum;cnt+=k.cnt;
	}
	while(sum>M)
	{
		sum-=o->v;
		--cnt;
		delmax(o);
	}
	ans=max(ans,cnt*L[u]);
	return HSJ(o,sum,cnt);
}
int n;
int main()
{
	freopen("1.in","r",stdin);
	freopen("1.out","w",stdout);
	scanf("%d%d",&n,&M);
	int master;
	for(int i=1;i<=n;++i)
	{
		int bi;
		scanf("%d%d%d",&bi,C+i,L+i);
		if(bi) sons[bi].push_back(i);
		else master=i;
	}
	src(master);
	std::cout<<ans<<std::endl;
	return 0;
}
