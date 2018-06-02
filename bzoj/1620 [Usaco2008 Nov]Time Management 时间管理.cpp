#include<cstdio>
#include<algorithm>
const int MAXN=1000+5;
struct Node{
	int T,S;
	bool operator<(const Node& rhs)const
	{
		return S>rhs.S;
	}
}a[MAXN];
int n;
int work()
{
	int t=a[0].S;
	for(int i=0;i<n;++i)
	{
		t-=a[i].T;
		if(i==n-1 && t>=0) return t;
		if(t<0) return -1;
		t=std::min(t,a[i+1].S);
	}
}
int main()
{
//	freopen("1.in","r",stdin);
	scanf("%d",&n);
	for(int i=0;i<n;++i)
		scanf("%d%d",&a[i].T,&a[i].S);
	std::sort(a,a+n);
	printf("%d\n",work());
	return 0;
}
