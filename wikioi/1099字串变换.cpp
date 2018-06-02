#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<queue>
#include<string>
#include<map>
using namespace std;
const int MAXR=6+2;
map<string,int> ms;
int ans=0;
struct node{
	string a[2];
}rule[MAXR];
int r=0;
string st,en;
bool expand(queue<string> &que,bool flag)
{
	ans++;
	if(ans>10) 
	{
		printf("NO ANSWER!\n");
		exit(0);
	}
	int n=que.size();
	while(n--)
	{
		string t=que.front();que.pop();
		for(int i=0;i<r;++i)
		{
			int pos=-1;
			while(1)
			{
				pos=t.find(rule[i].a[flag],pos+1);
				if(pos==t.npos) break;
				string t2=t;
				t2.replace(pos,rule[i].a[flag].length(),rule[i].a[!flag]);
				if(ms.count(t2)==0)
				{
					que.push(t2);
					ms[t2]=flag+1;
				}
				else
				{
					int ti=ms[t2];
					if(ti==flag+1) continue;
					else return 1;
				}
			}
		}
	}
	return 0;
}
void bfs()
{
	queue<string> que1,que2;
	que1.push(st);
	que2.push(en);
	ms[st]=1;
	ms[en]=2;
	while(!que1.empty() && !que2.empty())
	{
		if(expand(que1,0)) 
		{
			printf("%d\n",ans);
			exit(0);
		}
		if(expand(que2,1))
		{
			printf("%d\n",ans);
			exit(0);
		}
	}
}


int main()
{
	cin>>st>>en;
	while(cin>>rule[r].a[0])
	{
		cin>>rule[r++].a[1];
	}
	bfs();
	printf("NO ANSWER!\n");
	return 0;
}
