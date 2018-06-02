#include<cstdio>
#include<cstring>
const int MAXD=15+5;
typedef long long int64;
int64 temp[MAXD][MAXD];
int mod;
struct Mat{
	int n,m;
	int64 A[MAXD][MAXD];
	void init(int n,int m)
	{
		this->n=n;this->m=m;
		memset(A,0,sizeof(A));
	}
	void operator*=(const Mat& ret)
	{
		memset(temp,0,sizeof(temp));
		int p=ret.m;
		for(int i=0;i<n;++i)
			for(int j=0;j<p;++j)
				for(int k=0;k<m;++k)
					temp[i][j]=(temp[i][j]+A[i][k]*ret.A[k][j])%mod;
		memcpy(A,temp,sizeof(A));
		m=p;
	}
	void operator=(const Mat& ret)
	{
		memcpy(A,ret.A,sizeof(A));
		n=ret.n;m=ret.m;
	}
};
inline Mat Unit(int n)
{
	Mat ret;ret.init(n,n);
	for(int i=0;i<n;++i) ret.A[i][i]=1;
	return ret;
}
Mat Power(Mat ret,int e)
{
	Mat base=ret,ans=Unit(ret.n);
	while(e)
	{
		if(e&1) ans*=base;
		base*=base;
		e>>=1;
	}
	return ans;
}
Mat F,A;
int d,n;
int main()
{
	//freopen("1.in","r",stdin);
	while(scanf("%d%d%d",&d,&n,&mod)!=EOF && d)
	{
		F.init(d,1);A.init(d,d);
		for(int i=0;i<d;++i) scanf("%lld",&A.A[0][i]),A.A[0][i]%=mod;
		for(int i=1;i<d;++i) A.A[i][i-1]=1;
		for(int i=d-1;i>=0;--i) scanf("%lld",&F.A[i][0]),F.A[i][0]%=mod;
		if(n<=d) {printf("%lld\n",F.A[0][0]);continue;}
		A=Power(A,n-d);
		A*=F;
		printf("%lld\n",A.A[0][0]);
	}
	return 0;
}
