#include<cstdio>
#include<algorithm>
#include<cstring>
const int MAXN=128+5;
const int MAXM=11;
const int INF=1<<29;
int n,m,kase;
int c[MAXN];
int vis[1<<MAXM][1<<MAXM];
int dp[1<<MAXM][1<<MAXM]/*,cnt[1<<MAXM][1<<MAXM]*/;
char st[MAXM+2];
inline int judge(int s,int a)
{
	int t=s^a,cnt=0;
	for(int i=0;i<n;++i)
		if(((a&c[i])==a) && (~(~c[i]|t)==c[i]))
			++cnt;
	return cnt;
}
int src(int s,int a)
{
	int &ans=dp[s][a];
	if(vis[s][a]==kase) return ans;
	vis[s][a]=kase;
//	if(cnt[s][a]<=1) return ans=0;
//	if(cnt[s][a]==2) return ans=1;
	int cnt=judge(s,a);
	if(cnt<=1) return ans=0;
	if(cnt==2) return ans=1;
	ans=m;
	for(int i=0;i<m;++i)
	{
		int k=1<<i,t;
		if((s&k)==0) 
		{
			int s2=s|k,a2=a|k;
			//if(cnt[s2][a]>0 && cnt[s2][a2]>0)
			if(judge(s2,a)>0 && judge(s2,a2))
			{
				t=std::max(src(s2,a),src(s2,a2))+1;
				ans=std::min(t,ans);
			}
		}
	}
	return ans;
}
void init()
{
	for(int i=0;i<n;++i) c[i]=0;
	/*for(int s=0;s<(1<<m);++s)
	{
		for(int a=s;a;a=(a-1)&s) cnt[s][a]=0;
		cnt[s][0]=0;
	}*/
}
int main()
{
	//freopen("1.in","r",stdin);
	while(scanf("%d%d",&m,&n)!=EOF && m)
	{
		++kase;
		init();
		for(int i=0;i<n;++i)
		{
			scanf("%s",st);
			for(int j=0;j<m;++j)
				if(st[j]=='1') c[i]|=1<<j;
			//for(int s=0;s<(1<<m);++s) cnt[s][s&c[i]]++;
			//printf("%d\n",c[i]);
		}
		printf("%d\n",src(0,0));
	}
	return 0;
}
