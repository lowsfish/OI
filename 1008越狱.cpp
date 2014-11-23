#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
const int MOD=100003;
typedef long long LL;
LL pow_mod(LL a,LL b)
{
	if(a==0) return 0;
	LL ans=1;
	while(b)
	{
		if(b&1) ans=ans*a%MOD;
		a=a*a%MOD;
		b>>=1;
	}
	return ans;
}
LL m,n;
int main()
{
	cin>>m>>n;
	LL t1=pow_mod(m,n),t2=pow_mod(m-1,n-1);
	t2=t2*m%MOD;
	LL ans=t1-t2;
	while(ans<0) ans+=MOD;
	cout<<ans<<endl;
	return 0;
}
