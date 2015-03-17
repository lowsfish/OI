#include<cstdio>
#include<cstring>
typedef long long int64;
const int MAXN=200+5;
int64 tmp[MAXN][MAXN];
struct Mat{
	int n,m;
	int64 A[MAXN][MAXN];
	void operator*=(const Mat& M)
	{
		int p=M.m;
		memset(tmp,0,sizeof(tmp));
		for(int i=0;i<n;++i)
			for(int j=0;j<p;++j)
				for(int k=0;k<m;++k)
					tmp[i][j]+=A[i][k]*M.A[k][j];
		memcpy(A,tmp,sizeof A);
		m=p;
	}
}a,b;
void input(Mat& ret)
{
	scanf("%d%d",&ret.n,&ret.m);
	for(int i=0;i<ret.n;++i)
		for(int j=0;j<ret.m;++j)
			scanf("%lld",&ret.A[i][j]);
}
void print(Mat ret)
{
	for(int i=0;i<ret.n;++i)
		for(int j=0;j<ret.m;++j)
			printf("%lld%c",ret.A[i][j],j==ret.m-1?'\n':' ');
}
int main()
{
	input(a);input(b);
	a*=b;
	print(a);
	return 0;
}
