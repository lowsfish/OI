#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int T;
int n,m;
int ql,qr,v,p,k;	 
const int maxsz=800010;
int maxv[maxsz];
int query(int o,int L,int R)	//query the max value of[ql,qr]
{
	int M=L+(R-L)/2,ans=-1;
	if(ql<=L && qr>=R) return maxv[o];
	if(ql<=M) ans=max(ans,query(o*2,L,M));
	if(qr>M) ans=max(ans,query(o*2+1,M+1,R));
	return ans;
}

void update(int o,int L,int R)	//update A[p]=v
{
	int M=L+(R-L)/2;
	if(L==R) maxv[o]=v;
	else
	{
		if(p<=M) update(o*2,L,M);
		else update(o*2+1,M+1,R);
		maxv[o]=max(maxv[o*2],maxv[o*2+1]);
	}
}

void init()
{
	k=0;
	while((1<<k)<n) ++k;
	for(int i=0;i<=(1<<k);++i) maxv[i]=0;
}

int build(int o,int L,int R)
{
	int M=L+(R-L)/2;
	if(L==R) return maxv[o];
	maxv[o]=max(build(o*2,L,M),build(o*2+1,M+1,R));
	return maxv[o];	
}

int main()
{
	//freopen("1.in","r",stdin);
	ios::sync_with_stdio(false);
	while(cin>>n>>m)
	{
		init();
		for(int i=1;i<=n;++i)
		{
			cin>>maxv[(1<<k)+i-1];
			//scanf("%d",&maxv[(1<<k)+i-1]);
		}
		build(1,1<<k,1<<(k+1));
		for(int i=0;i<m;++i)
		{
			char c;
			cin>>c;
			/*char s[5];
			scanf("%s",s);
			c=s[0];*/
			if(c=='Q')
			{
				cin>>ql>>qr;
				cout<<query(1,1,1<<k)<<endl;
			}
			else
			{
				cin>>p>>v;
				update(1,1,1<<k);
			}
		}
	}
	return 0;
}
