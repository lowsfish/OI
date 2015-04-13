#include<cstdio>
#include<list>
#define pb push_back
int n,k;
typedef std::list<int>::iterator it;
std::list<int> lt;
int work()
{
	lt.pb(n);
	while(1)
	{
		bool up=0;
		for(it i=lt.begin();i!=lt.end();++i)
			if((*i-k)%2==0 && *i>k)
				up=1,lt.pb((*i-k)/2),lt.pb((*i-k)/2+k),lt.erase(i++);
		if(!up) return lt.size();
	}
}
int main()
{
	scanf("%d%d",&n,&k);
	printf("%d\n",work());
	return 0;
}
