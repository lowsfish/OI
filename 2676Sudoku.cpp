#include<iostream>
#include<cstdio>
#include<cstring>
#define MAXSZ 10
using namespace std;
typedef pair<int,int> P;
P blank[MAXSZ*MAXSZ];
int num;
int line[MAXSZ][MAXSZ],row[MAXSZ][MAXSZ],grid[MAXSZ][MAXSZ];
int su[MAXSZ][MAXSZ];
void init()
{
	num=0;
	memset(line,0,sizeof(line));
	memset(row,0,sizeof(row));
	memset(grid,0,sizeof(grid));
	memset(su,0,sizeof(su));
}

bool dfs(int cur)
{
	if(cur<0) return 1;
	int x=blank[cur].first,y=blank[cur].second;
	int k=x/3*3+y/3;
	for(int i=1;i<=9;++i)
	{
		if(!line[x][i] && !row[y][i] && !grid[k][i])
		{
			su[x][y]=i;
			line[x][i]=row[y][i]=grid[x/3*3+y/3][i]=1;
			if(dfs(cur-1)) return 1;
			su[x][y]=line[x][i]=row[y][i]=grid[k][i]=0;
		}
	}
	return 0;
}

void print()
{
	for(int i=0;i<9;++i)
	{
		for(int j=0;j<9;++j)
			cout<<su[i][j];
		cout<<endl;
	}
}
int main()
{
	freopen("1.in","r",stdin);
	int T;
	cin>>T;
	cin.get();
	while(T--)
	{
		init();
		for(int i=0;i<9;++i)
		{
			char temp[MAXSZ];
			cin.getline(temp,MAXSZ);
			for(int j=0;j<9;++j)
			{
				su[i][j]=temp[j]-'0';
				if(su[i][j])
				{
					int t=su[i][j],k=i/3*3+j/3;
					line[i][t]=row[j][t]=grid[k][t]=1;
				}
				else
				{
					blank[num].first=i;
					blank[num++].second=j;
				}
			}
		}
		dfs(num-1);
		print();
	}
	return 0;
}
