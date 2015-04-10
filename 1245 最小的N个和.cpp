#include<cstdio>
#include<queue>
#include<algorithm>
const int MAXN=100000+5;
int a[MAXN],b[MAXN];
typedef std::pair<int,int> P;	//a[i]+b[j]的和 和 j的值 
#define fr first
#define sc second
void merge(int*A,int*B,int*C,int n)
{
	std::priority_queue<P,std::vector<P>,std::greater<P> >que;
	for(int i=0;i<n;++i) que.push(P(A[i]+B[0],0));
	for(int i=0;i<n;++i)
	{
		P p=que.top();que.pop();
		C[i]=p.fr;
		if(p.sc+1<n) que.push(P(p.fr-B[p.sc]+B[p.sc+1],p.sc+1));
	}
}
int n;
int ans[MAXN];
int main()
{
	scanf("%d",&n);
	for(int i=0;i<n;++i) scanf("%d",a+i);
	for(int i=0;i<n;++i) scanf("%d",b+i);
	std::sort(a,a+n);
	std::sort(b,b+n);
	merge(a,b,ans,n);
	for(int i=0;i<n;++i) printf("%d%c",ans[i],i==n-1?'\n':' ');
	return 0;
}
