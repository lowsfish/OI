#include<iostream>
#include<stdio.h>
#include<string>
#include<cstring>
using namespace std;
int n,p1,p2;
int s1[5005],s2[5005];
string str1,str2;
struct node{
	int st[26],en[26],cou[26];
};
node dp[2][5005],c;
void pri(int a,int b)
{
	int sum=0;
	for(int i=0;i<26;i++)
		if(dp[a%2][b].cou[i]>1)
			sum+=dp[a%2][b].en[i]-dp[a%2][b].st[i];
	cout<<sum<<endl;
}
node add(node a,int s,int p)
{
	node ans=a;
	if(ans.cou[s])
		ans.en[s]=p;
	else
		ans.st[s]=p;
	ans.cou[s]++;
	return ans;
}
node minnum(node s1,node s2)
{
	int sum1=0,sum2=0;
	for(int i=0;i<26;i++)
	{
		if(s1.cou[i]>1)
			sum1+=s1.en[i]-s1.st[i];
		if(s2.cou[i]>1)
			sum2+=s2.en[i]-s2.st[i];
	}
	return sum1>sum2?s2:s1;
}
void init(void)
{
	p1=0,p2=0;
	int len1=str1.length(),len2=str2.length();
	while(p1<=len1)
	{
		s1[p1]=(int)(str1[p1]-'A');
		p1++;
	}
	while(p2<=len2)
	{
		s2[p2]=(int)(str2[p2]-'A');
		p2++;
	}
	dp[0][0]=c;
}
int main(void)
{
	freopen("1.in","r",stdin);
	scanf("%d",&n);
	for(int t=0;t<n;t++)
	{
		cin>>str1;
		cin>>str2;
		init();
		for(int i=0;i<p1;i++)
			for(int j=0;j<p2;j++)
			if(i || j)
			{
				dp[i%2][j]=minnum(
							i>0?add(dp[(i-1)%2][j],s1[i],i):c,
							j>0?add(dp[i%2][j-1],s2[j],j):c);
			//	cout<<dp[i%2][j]<<endl;
			}
		pri(p2-1,p2-1);
	}
	return 0;
}
