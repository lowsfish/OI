#include<cstdio>
#include<ext/rope>
__gnu_cxx::crope s;
int t,cur;
char op[5],buf[1<<21];
int main()
{
	for(scanf("%d",&t);t--;)
	{
		scanf("%s",op);
		int k,i;
		switch(op[0])
		{
			case 'M':scanf("%d",&cur);
					 break;
			case 'I':scanf("%d",&k);
					 getchar();
					 i=0;
					 while(k)
					 {
					 	char c=getchar();
						if(c>=32 && c<=126)
						{
							buf[i++]=c;
							--k;
						}
					 }
					 buf[i]=0;
					 s.insert(cur,buf);
					 break;
			case 'D':scanf("%d",&k);
					 s.erase(cur,k);
					 break;
			case 'G':scanf("%d",&k);
					 puts(s.substr(cur,k).c_str());
					 break;
			case 'P':--cur;
					 break;
			case 'N':++cur;
					 break;
		}
	}
	return 0;
}
