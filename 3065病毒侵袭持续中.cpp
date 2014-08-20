#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
using namespace std;
const int MAXNODE=1000*50+10;
const int MAXL=50+10;
const int MAXLEN=2000000;
const int SIGMA_SIZE=26;
const int MAXN=1000+10;
char s[MAXN][MAXL];
int N;
char T[MAXLEN];
class AhoCorasick{
private:
	int ch[MAXNODE][SIGMA_SIZE];
	int f[MAXNODE],last[MAXNODE],val[MAXNODE];
	int cnt[MAXNODE];
	int sz;
	int idx(char c)
	{
		return c-'A';
	}
public:
	void init()
	{
		memset(ch[0],0,sizeof(ch[0]));
		sz=1;
		memset(cnt,0,sizeof(cnt));
	}

	void insert(char *s,int v)
	{
		int n=strlen(s),u=0;
		for(int i=0;i<n;++i)
		{
			int c=idx(s[i]);
			if(!ch[u][c])
			{
				memset(ch[sz],0,sizeof(ch[sz]));
				val[sz]=0;
				ch[u][c]=sz++;
			}
			u=ch[u][c];
		}
		val[u]=v;
	}
	void getfail()
	{
		queue<int>que;
		for(int c=0;c<SIGMA_SIZE;++c)
		{
			int u=ch[0][c];
			if(u)
			{
				last[u]=0;
				que.push(u);
				f[u]=0;
			}
		}
		while(!que.empty())
		{
			int r=que.front();que.pop();
			for(int c=0;c<SIGMA_SIZE;++c)
			{
				int u=ch[r][c];
				if(!u) continue;
				que.push(u);
				int v=f[r];
				while(v && !ch[v][c]) v=f[v];
				f[u]=ch[v][c];
				last[u]=val[f[u]]?f[u]:last[f[u]];
			}
		}
	}

	void count(int j)
	{
		if(j && val[j])
		{
			cnt[val[j]]++;
			count(last[j]);
		}
	}

	void find(char *T)
	{
		int n=strlen(T),j=0;
		for(int i=0;i<n;++i)
		{
			int c=idx(T[i]);
			if(c<0 || c>=26)
			{
				j=0;
				continue;
			}
			while(j && !ch[j][c]) j=f[j];
			j=ch[j][c];
			if(val[j]) count(j);
			else if(last[j]) count(last[j]);
		}	
	}

	void print()
	{
		for(int i=1;i<=N;++i)
		{
			if(cnt[i]) printf("%s: %d\n",s[i],cnt[i]);
		}
	}
}ac;

int main()
{
	//freopen("1.in","r",stdin);
	while(scanf("%d",&N)==1)
	{
		ac.init();
		for(int i=1;i<=N;++i)
		{
			scanf("%s",s[i]);
			ac.insert(s[i],i);
		}	
		ac.getfail();
		scanf("%s",T);
		ac.find(T);
		ac.print();
	}
	return 0;
}
