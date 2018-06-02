#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<set>
#include<queue>
#include<vector>
#include<algorithm>
using namespace std;
inline int Abs(int x) {return x<0?-x:x;}
const int INF=1<<30;
struct Node{
	int Min;
	multiset<int> S;
	typedef set<int>::iterator it;
	Node():Min(INF) {}
	void ins(int x)
	{
		it j=S.insert(x);
		if(j!=S.begin())
		{
			Min=min(Min,abs(x-*(--j)));
			++j;
		}
		++j;
		if(j!=S.end())
		{
			Min=min(Min,abs(x-*(j)));
		}
	}
}All;
const int MAXN=500000+5;
vector<int> List[MAXN];
struct State{
	bool inside;
	int val,i,x;
	State(bool in,int val,int i,int x):inside(in),val(val),i(i),x(x) {}
	bool legal() const
	{
		return inside || (x==List[i].size()-1);
	}
	bool operator<(const State& rhs) const
	{
		return val>rhs.val;
	}
};

int n,m;
priority_queue<State> que;

void ins(int x,int i)
{
	List[i].push_back(x);
	int sz=List[i].size()-1;
	que.push(State(1,abs(x-List[i][sz-1]),i,sz));
	if(i!=n-1) que.push(State(0,abs(x-List[i+1].front()),i,sz));
}

int query()
{
	while(!que.empty() && !que.top().legal()) que.pop();
	return que.top().val;
}

int main()
{
	//freopen("1.in","r",stdin);
	char s[50];
	scanf("%d%d",&n,&m);
	for(int i=0;i<n;++i)
	{
		int t;
		scanf("%d",&t);
		List[i].push_back(t);
		All.ins(t);
		if(i!=0)
			que.push(State(0,abs(t-List[i-1][0]),i,0));
	}
	while(m--)
	{
		scanf("%s",s);
		if(s[0]=='I')
		{
			int i,x;
			scanf("%d%d",&i,&x);
			--i;
			ins(x,i);
			All.ins(x);
		}
		else if(s[4]=='S')
		{
			printf("%d\n",All.Min);
		}
		else
		{
			printf("%d\n",query());
		}
	}
	return 0;
}
