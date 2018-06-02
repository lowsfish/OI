#include<algorithm>
#include<vector>
#include<map>
#include<string>
#include<iostream>
#include<cstdio>
#include<cstring>
const int MAXN=200+10;
int n;
std::vector<int> son[MAXN];
std::map<std::string,int> si;
int dp[MAXN][2];		//dp[i][0]:unuse i	dp[i][1]:use i
bool f[MAXN][2];
int src(int u,bool flag)
{
	if(dp[u][flag]>0) return dp[u][flag];
	if(son[u].empty())
	{
		f[u][flag]=1;
		return flag;
	}
	int ans=0;
	bool only=1;
	if(flag)
	{
		for(int i=0;i<son[u].size();++i)
		{
			ans+=src(son[u][i],0);
			if(!f[son[u][i]][0]) only=0;
		}
	}
	else
	{
		for(int i=0;i<son[u].size();++i)
		{
			int t1=src(son[u][i],0),t2=src(son[u][i],1);
			ans+=std::max(t1,t2);
			if(t1==t2) only=0;
			else if(!f[son[u][i]][t1<t2]) only=0;
		}
	}
	f[u][flag]=only;
	ans+=flag;
	return dp[u][flag]=ans;
}
void init()
{
	for(int i=0;i<=n;++i)
	{
		son[i].clear();
	}
	memset(dp,0,sizeof(dp));
	memset(f,0,sizeof(f));
	si.clear();
}
int main()
{
	//freopen("1.in","r",stdin);
	while(std::cin>>n && n)
	{
		init();
		int num=0;
		std::string a,b;
		std::cin>>a;
		si[a]=num++;
		for(int i=1;i<n;++i)
		{
			std::cin>>a>>b;
			if(!si.count(a)) si[a]=num++;
			if(!si.count(b)) si[b]=num++;
			son[si[b]].push_back(si[a]);
		}
		int t1=src(0,0),t2=src(0,1);
		//printf("%d %d\n",t1,t2);
		bool only=1;
		if(t1==t2) only=0;
		else if(!f[0][t1<t2]) only=0;
		printf("%d %s\n",std::max(t1,t2),only?"Yes":"No");
	}
	return 0;
}
