#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<queue>
using namespace std;
struct Seg{
	int begin,end;
	Seg(int begin,int end):begin(begin),end(end){}
	bool operator <(const Seg &a) const
	{
		return end>a.end || (end==a.end && begin>a.begin);
	}
};

priority_queue<Seg> que;
int main()
{
	//freopen("1.in","r",stdin);
	int n;
	cin>>n;
	for(int i=0;i<n;++i)
	{
		int a,b;
		cin>>a>>b;
		if(a>b) swap(a,b);
		que.push(Seg(a,b));
	}
	int t=que.top().end;que.pop();
	int ans=1;
	while(!que.empty())
	{
		if(que.top().begin>=t)
		{
			++ans;
			t=que.top().end;
		}
		que.pop();
	}
	cout<<ans<<endl;
}
