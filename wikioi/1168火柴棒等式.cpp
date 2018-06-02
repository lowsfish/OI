#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
int a[]={6,2,5,5,4,5,6,3,7,6};
int getsum(int i)
{
	if(i==0) return 6;
	int ans=0;
	while(i)
	{
		ans+=a[i%10];
		i/=10;
	}
	return ans;
}
int main()
{
	freopen("1.in","r",stdin);
	int n,i,j,tot=0;
	cin>>n;
	n-=4;
	if(n<=0)
	{
		cout<<'0'<<endl;
		return 0;
	}
	for(i=0;i<999;++i)
		for(j=0;j<999;++j)
		{
			int x=i+j;
			if(getsum(i)+getsum(j)+getsum(x)==n)
			{
				//cout<<i<<' '<<j<<' '<<x<<endl;
				++tot;
			}
		}
	cout<<tot<<endl;
	return 0;
}
