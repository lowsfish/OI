#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
using namespace std;
const int SIGMA_SIZE=26;
const int MAXNODE=10000*50+10;
const int MAXL=10000+10;
const int MAXLEN=1000000+10;
char mo[MAXLEN];
struct AhoCorasick{
	int ch[MAXNODE][SIGMA_SIZE];
	int val[MAXNODE][2];
	bool used[MAXNODE];
	int last[MAXNODE];
	int f[MAXNODE];
	int sz;
	int res;
	void init () 
	{
		sz=1;
		memset(ch[0],0,sizeof(ch[0]));
		res=0;
		memset(used,0,sizeof(used));
		memset(val,0,sizeof(val));
	}
	int idx(char c) {return c-'a';}
	void insert(char *s,int v)
	{
		int u=0,n=strlen(s);
		for(int i=0;i<n;++i)
		{
			int c=idx(s[i]);
			if(!ch[u][c])
			{
				memset(ch[sz],0,sizeof(ch[sz]));
				val[sz][0]=0;
				ch[u][c]=sz++;
			}
			u=ch[u][c];
		}
		val[u][0]=v;
		val[u][1]++;	//处理关键字重复情况
	}

	void count(int j)
	{
		if(j && !used[val[j][0]])	//注意重复出现只算一次
		{
			res+=val[j][1];
			used[val[j][0]]=1;
			count(last[j]);
		}
	}

	void find(char *T)
	{
		int n=strlen(T);
		int j=0;
		for(int i=0;i<n;++i)
		{
			int c=idx(T[i]);
			while(j && !ch[j][c]) j=f[j];
			j=ch[j][c];
			if(val[j]) count(j);
			else if(last[j]) count(last[j]);
		}
	}

	void getfail()
	{
		queue<int> q;
		f[0]=0;
		for(int c=0;c<SIGMA_SIZE;++c)
		{
			int u=ch[0][c];
			if(u)
			{
				f[u]=0;
				q.push(u);
				last[u]=0;
			}
		}
		while(!q.empty())
		{
			int r=q.front();q.pop();
			for(int c=0;c<SIGMA_SIZE;++c)
			{
				int u=ch[r][c];
				if(!u) continue;
				q.push(u);
				int v=f[r];
				while(v && !ch[v][c]) v=f[v];
				f[u]=ch[v][c];
				last[u]=val[f[u]]?f[u]:last[f[u]];
			}
		}
	}
} ac;
int main()
{
	//freopen("1.in","r",stdin);
	int T;
	scanf("%d",&T);
	while(T--)
	{
		int n;
		ac.init();
		scanf("%d",&n);
		for(int i=1;i<=n;++i)
		{
			char s[MAXL];
			scanf("%s",s);
			ac.insert(s,i);
		}
		scanf("%s",mo);
		ac.getfail();
		ac.find(mo);
		printf("%d\n",ac.res);
	}
	return 0;
}
