#include<cstdio>
#include<string>
#include<cstring>
#include<algorithm>
#include<iostream>
typedef long long LL;
LL num[]={0,9,9,90,90,900,900,9000,9000,90000,90000,900000,900000,9000000,9000000,90000000,90000000,900000000,900000000,9000000000LL};
using std::string;
string int_to_string(int x) {
	char s[50];
	sprintf(s,"%d",x);
	return string(s);
}
LL ten[]={0,0,0,10,10,100,100,1000,1000,10000,10000,100000,100000,1000000,1000000,10000000,10000000,100000000,100000000,1000000000,1000000000};
int main() {
	int n;
	while(scanf("%d",&n)!=EOF && n) {
		LL t=0;
		int i;
		for(i=1;t+num[i]<n;++i) t+=num[i];
		n-=t;
		n+=ten[i];
		if(i>2) --n;
		string ans=int_to_string(n);
		string nans=ans;
		if(i&1) nans.erase(--nans.end());
		std::reverse(nans.begin(),nans.end());
		ans+=nans;
		std::cout<<ans<<std::endl;
	}
	return 0;
}
