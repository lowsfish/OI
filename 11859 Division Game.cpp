#include<cstdio>
#include<cmath>
const int MAXN=50+5;
const int MAXV=10000+5;
int nim[MAXN];
int prime[MAXV];
bool vis[MAXV];
int p;
int n,m;
void init()
{
	int s=sqrt(MAXV)+1;
	for(int i=2;i<=s;++i) if(!vis[i])
		for(int j=i*i;j<MAXV;j+=i) vis[j]=1;
	for(int i=2;i<MAXV;++i) if(!vis[i]) prime[p++]=i;
}
int main()
{
	int T;
	scanf("%d",&T);
	init();
	for(int kase=1;kase<=T;++kase)
	{
		scanf("%d%d",&n,&m);
		for(int i=0;i<n;++i)
		{
			int res=0;
			for(int j=0;j<m;++j)
			{
				int t;
				scanf("%d",&t);
				int k=0;
				while(t>1)
				{
					while(t%prime[k]==0) t/=prime[k],++res;
					++k;
					if(k>=p || prime[k]>t) break;
				}
			}
			nim[i]=res;
		}
		int t=0;
		for(int i=0;i<n;++i) t^=nim[i];
		printf("Case #%d: %s\n",kase,t?"YES":"NO");
	}
	return 0;
}
