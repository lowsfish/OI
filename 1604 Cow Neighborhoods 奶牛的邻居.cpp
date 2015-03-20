#include<cstdio>
#include<set>
#include<cmath>
#include<algorithm>
const int MAXN=100000+10;
struct Point
{
	int x,y,pos;
	Point(int x=0,int y=0,int pos=0):x(x),y(y),pos(pos) {}
	bool operator<(const Point& rhs)const
	{
		return y<rhs.y || (y==rhs.y && x<rhs.x);
	}
}p[MAXN];
bool cmp(const Point& a,const Point& b)
{
	return a.x<b.x;
}
int n,c,ans;
int pa[MAXN];
std::set<Point> st;
typedef std::set<Point>::iterator ite;
int find(int x)
{
	return pa[x]==x?x:pa[x]=find(pa[x]);
}
void unite(int x,int y)
{
	x=find(x);y=find(y);
	if(x==y) return;
	--ans;pa[x]=y;
}
void solve()
{
	int qh=0;
	ans=n;
	for(int i=1;i<n;++i) pa[i]=i;
	st.insert(p[0]);
	for(int i=1;i<n;++i)
	{
		while(p[i].x-p[qh].x>c)
			st.erase(p[qh++]);
		ite it=st.lower_bound(p[i]);
		if(it!=st.end())
			if(abs(p[i].y-it->y)<=c)
				unite(p[i].pos,it->pos);
		if(it!=st.begin())
		{
			--it;
			if(abs(p[i].y-it->y)<=c)
				unite(p[i].pos,it->pos);
		}
		st.insert(p[i]);
	}
}
int tot[MAXN];
int main()
{
	//freopen("1.in","r",stdin);
	scanf("%d%d",&n,&c);
	for(int i=0;i<n;++i)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		p[i]=Point(x+y,x-y,i);
	}
	std::sort(p,p+n,cmp);
	solve();
	int mx=0;
	for(int i=0;i<n;++i) tot[find(i)]++,mx=std::max(mx,tot[find(i)]);
	printf("%d %d\n",ans,mx);
	return 0;
}
