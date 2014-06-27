#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#define MAXSZ 110
using namespace std;
typedef pair<int,int> P;
const int INF=(1<<29);
struct node{
	P po[4];
}*a;
int T[MAXSZ];
double mat[MAXSZ<<2][MAXSZ<<2];
/*double getslope(P a,P b)	//获取斜率
{
	if(a.first == b.first) return (double)INF;
	double dx=a.first-b.first,dy=a.second-b.second;
	return dy/dx;
}*/

double getdis(const P a,const P b)
{
	double dx=a.first-b.first,dy=a.second-b.second;
	return sqrt(dx*dx+dy*dy);
}

void getforth(node &x)				//获取第四个点
{
	P A=x.po[0], B=x.po[1], C=x.po[2], &D=x.po[3];
	D.first=C.first+(B.first-A.first);
	D.second=C.second+(B.second-A.second);
	if(fabs(getdis(A,D)-getdis(B,C)) <= 1e-6) return;
	D.first=C.first+(A.first-B.first);
	D.second=C.second+(A.second-B.second);
	if(fabs(getdis(A,C)-getdis(B,D))<=1e-6) return;
	D.first=A.first+(B.first-C.first);
	D.second=A.second+(B.second-C.second);
	return;
}

void input(int s)
{
	for(int i=0;i<s;++i)
	{
		for(int j=0;j<3;++j)
			cin>>a[i].po[j].first>>a[i].po[j].second;
		cin>>T[i];
		//cout<<T[i]<<endl;
		getforth(a[i]);
		//cout<<a[i].po[3].first<<' '<<a[i].po[3].second<<endl;
	}
}
int main()
{
	//freopen("1.in","r",stdin);
	int n;
	cin>>n;
	while(n--)
	{
		int s,t,S,E;		//s是城市个数，t是飞机单位里程价格
							//S是起点，T是终点
		int i,j;
		cin>>s>>t>>S>>E;
		a=new node[s];
		input(s);
		memset(mat,0,sizeof(mat));
		for(i=0;i<4*s;++i)
			for(j=0;j<4*s;++j)
			{
				if(i==j) mat[i][j]=0;
				else if(i/4 == j/4) mat[i][j]=getdis(a[i/4].po[i%4],a[j/4].po[j%4])*T[i/4];
				else mat[i][j]=getdis(a[i/4].po[i%4],a[j/4].po[j%4])*t;
			}
	for(int k=0;k<4*s;++k)
		for(i=0;i<4*s;++i)		//Floyd
			for(j=0;j<4*s;++j)
				{
					mat[i][j]=min(mat[i][j],mat[i][k]+mat[k][j]);
				}
		double ans=(double)INF;
		for(i=4*(S-1);i<4*S;++i)
			for(j=4*(E-1);j<4*E;++j)
			{
				//cout<<mat[i][j]<<endl;
				ans=min(ans,mat[i][j]);
			}
		printf("%.1f\n",ans);
		delete []a;
	}
}
