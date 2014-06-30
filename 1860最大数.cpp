#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#define MAXSZ 50
using namespace std;
struct item{
       int n;
       item(int s):n(s){}
       bool operator < (const item &a)const
       {
            char s1[MAXSZ],s2[MAXSZ];
            sprintf(s1,"%d\0",n);
            sprintf(s2,"%d\0",a.n);
            if(s1[0]!=s2[0]) return s1[0]<s2[0];
            int i;
            for(i=0;s1[i] == s2[i];++i)
                if(s1[i]==0) return 0;
            if(s1[i]==0 && s2[i]!=0) return s1[0]<s2[i];
            if(s1[i]!=0 && s2[i]==0) return s1[0]>s1[i];    //注意这里是大于号
                                            //因为如果是这种情况的话当前数需要后取出 
            return s1[i]<s2[i];
       }
};

int main()
{
    priority_queue<item> que;
    int n;
    cin>>n;
    for(int i=0;i<n;++i)
    {
            int k;
            cin>>k;
            que.push(item(k));
            }
    while(!que.empty())
    {
                       cout<<que.top().n;
                       que.pop();
                       }
    cout<<endl;
    return 0;
    
    }
