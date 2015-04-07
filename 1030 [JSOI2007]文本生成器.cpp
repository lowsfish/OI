#include<cstdio>
#include<cstring>
#include<algorithm>
const int MAXN=60+5;
const int MAXL=100+5;
const int SIGMA_SIZE=26;
struct Trie{
    Trie* ch[SIGMA_SIZE],*fail;
    Trie* jump[SIGMA_SIZE];
    bool hasWord;
    int id;
    static int numId;
    Trie(){
        id=numId++;
        memset(ch,0,sizeof ch);
        fail=0;
        hasWord=0;
    }
    Trie* getch(char c)
    {
        int w=c-'A';
        if(ch[w]==NULL)
            ch[w]=new Trie;
        return ch[w];
    }
};
int Trie::numId=0;
Trie* root;
int n,m;
char s[MAXL];
void input()
{
    root=new Trie;
    scanf("%d%d",&n,&m);
    while(n--)
    {
        scanf("%s",s);
        int len=strlen(s);
        Trie* t=root;
        for(int i=0;i<len;++i)
            t=t->getch(s[i]);
        t->hasWord=1;
    }
}
const int MAXNODE=MAXL*MAXN;
Trie* que[MAXNODE];
int qh,qt;
void build()
{
    qh=qt=0;
    que[qt++]=root;
    while(qh<qt)
    {
        Trie* u=que[qh++];
        for(int i=0;i<SIGMA_SIZE;++i) if(u->ch[i])
        {
            Trie* v=u->ch[i];
            Trie* p=u->fail;
            while(p && !p->ch[i]) p=p->fail;
            if(!p) v->fail=root;
            else v->fail=p->ch[i];
            v->hasWord|=v->fail->hasWord;
            que[qt++]=v;
        }
    }
    for(int i=0;i<qt;++i)
    {
        Trie* u=que[i];
        for(int i=0;i<SIGMA_SIZE;++i)
        {
            Trie* t=u;
            while(t && !t->ch[i]) t=t->fail;
            if(!t) u->jump[i]=root;
            else u->jump[i]=t->ch[i];
        }
    }
}
const int MOD=10007;
int dp[MAXL][MAXNODE][2];
int src(int len,Trie* u,bool hasWord)
{
    if(len==0) return (int)hasWord;
    int&ans=dp[len][u->id][hasWord];
    if(ans!=-1) return ans;
    ans=0;
    for(int i=0;i<SIGMA_SIZE;++i)
        ans=(ans+src(len-1,u->jump[i],hasWord|u->jump[i]->hasWord))%MOD;
    return ans;
}
int main()
{
//  freopen("1.in","r",stdin);
    input();
    build();
    memset(dp,-1,sizeof dp);
    printf("%d\n",src(m,root,0));
    return 0;
}
