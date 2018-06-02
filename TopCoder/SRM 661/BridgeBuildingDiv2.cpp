#include <cstdio>
#include <cmath>
#include <cstring>
#include <ctime>
#include <iostream>
#include <algorithm>
#include <set>
#include <vector>
#include <sstream>
#include <typeinfo>
#include <fstream>

using namespace std;

const int INF=~0U>>2;
const int MAXN=15;
int ar[MAXN];
vector<int> a,b;
int mat[MAXN<<1][MAXN<<1];
class BridgeBuildingDiv2 {
	int ans;
	int n,k;
	int calc()
	{
		memset(mat,-1,sizeof(mat));
		for(int i=0;i<n-1;++i)
			mat[i][i+1]=mat[i+1][i]=a[i];
		for(int i=0;i<n-1;++i)
			mat[i+n][i+n+1]=mat[i+n+1][i+n]=b[i];
		for(int i=0;i<2*n;++i)
			for(int j=0;j<2*n;++j)
			{
				if(mat[i][j]!=-1) continue;
				if(i==j) mat[i][j]=0;
				else mat[i][j]=INF;
			}
		for(int i=0;i<k;++i) mat[ar[i]][ar[i]+n]=mat[ar[i]+n][ar[i]]=0;
		int res=0;
		for(int k=0;k<n*2;++k)
			for(int i=0;i<n*2;++i)
				for(int j=0;j<n*2;++j)
					mat[i][j]=min(mat[i][j],mat[i][k]+mat[k][j]);
		for(int i=0;i<n*2;++i)
			for(int j=0;j<n*2;++j)
				res=max(res,mat[i][j]);
				//printf("%d\n",mat[i][j]);
		return res;
	}
	void dfs(int cur,int dep)
	{
		if(dep==k)
		{
			ans=min(ans,calc());
			return;
		}
		for(int i=cur;i<n;++i)
		{
			ar[dep]=i;
			dfs(i+1,dep+1);
		}
	}
    public:
    int minDiameter(vector<int> _a, vector<int> _b, int K) {
		a=_a;b=_b;
		n=a.size()+1;k=K;
		ans=INF;
		dfs(0,0);
		return ans;
    }
};

