#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#include<vector>
#include<string>
const int MAXN=3000+5;
using std::vector;
using std::string;
vector<int> G[MAXN];
typedef vector<int>::iterator vit;
char str1[MAXN],str2[MAXN];
int fa[MAXN];
string s1,s2;
void build(char* s)
{
	int u=0,num=0,len=strlen(s);
	for(int i=0;i<=len;++i) G[i].clear();
	for(char* p=s;*p;++p)
	{
		if(*p=='0')
		{
			G[u].push_back(++num);
			fa[num]=u;
			u=num;
		}
		else u=fa[u];
	}
}
string get_str(int u)
{
	string ans="(";
	std::priority_queue<string,vector<string>,std::greater<string> > que;
	for(vit e=G[u].begin();e!=G[u].end();++e)
		que.push(get_str(*e));
	while(!que.empty())
	{
		ans+=que.top();
		que.pop();
	}
	ans+=')';
	return ans;
}
int main()
{
	int T;
	for(scanf("%d",&T);T--;)
	{
		scanf("%s%s",str1,str2);
		build(str1);
		s1=get_str(0);
		build(str2);
		s2=get_str(0);
		if(s1==s2) puts("same");
		else puts("different");
	}
	return 0;
}
