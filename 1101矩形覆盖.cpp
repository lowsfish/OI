#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
const int MAXK=4+2;
const int MAXN=50+5;
const int INF=1<<20;
typedef pair<int,int> P;
struct square{
	P p1,p2;
	int S;
	square() {p1.first=p1.second=INF;p2.first=p2.second=-1;S=0;}
	void getS()
	{
		if(p1.first==INF) S=0;
		else S=(p2.second-p1.second)*(p2.first-p1.first);
	}
	void print()
	{
		printf("%d %d %d %d\n",p1.first,p1.second,p2.first,p2.second);
	}
}a[MAXK];
int n,k;
P ps[MAXN];
int ans=INF;
int St=0;

bool judge(P ju,int cur=-1)
{
	int fi=ju.first,se=ju.second;
	for(int i=0;i<k;++i)
	{
		if(i==cur) continue;	
		   	if(fi>=a[i].p1.first && fi<=a[i].p2.first && se>=a[i].p1.second && se<=a[i].p2.second) return 0;
	}
	return 1;
}

bool judge2(int cur)
{
	if(judge(a[cur].p1,cur) && judge(a[cur].p2,cur) && judge(P(a[cur].p1.first,a[cur].p2.second),cur) && judge(P(a[cur].p2.first,a[cur].p1.second),cur)) return 1;
	return 0;
}
void dfs(int cur)
{
	if(cur==n) 
	{
		ans=min(ans,St);
		return;
	}
	if(!judge(ps[cur])) dfs(cur+1);
	else
	{
		for(int i=0;i<k;++i)
		{
			square tt=a[i];
			int ss=a[i].S;
			int &x1=a[i].p1.first,&x2=a[i].p2.first,&y1=a[i].p1.second,&y2=a[i].p2.second;
			x1=min(x1,ps[cur].first);
			y1=min(y1,ps[cur].second);
			x2=max(x2,ps[cur].first);
			y2=max(y2,ps[cur].second);
			a[i].getS();
			int sss=St;
			St+=a[i].S-ss;
			if(St<ans && judge2(i)) dfs(cur+1);
			St=sss;
			a[i]=tt;
		}
	}
}
int main()
{
	scanf("%d%d",&n,&k);
	for(int i=0;i<n;++i)
	{
		scanf("%d%d",&ps[i].first,&ps[i].second);
	}
	dfs(0);
	printf("%d\n",ans);
	return 0;
}
