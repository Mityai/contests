#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <set>
#include <queue>
#include <map>
#include <cstdio>
#include <iomanip>
#include <sstream>
#include <iostream>
#include <cstring>
#include <complex>
#define REP(i,x,v)for(int i=x;i<=v;i++)
#define REPD(i,x,v)for(int i=x;i>=v;i--)
#define FOR(i,v)for(int i=0;i<v;i++)
#define FORE(i,t) for (typeof(t.begin()) i=t.begin(); i!=t.end(); i++)
#define REMIN(x,y) (x)=min((x),(y))
#define REMAX(x,y) (x)=max((x),(y))
#define pb push_back
#define sz size()
#define mp make_pair
#define fi first
#define se second
#define ll long long
#define IN(x,y) ((y).find((x))!=(y).end())
#define un(v) v.erase(unique(ALL(v)),v.end())
#define LOLDBG
#ifdef LOLDBG
#define DBG(vari) cerr<<#vari<<" = "<<vari<<endl;
#define DBG2(v1,v2) cerr<<(v1)<<" - "<<(v2)<<endl;
#else
#define DBG(vari)
#define DBG2(v1,v2)
#endif
#define CZ(x) scanf("%d",&(x));
#define CZ2(x,y) scanf("%d%d",&(x),&(y));
#define CZ3(x,y,z) scanf("%d%d%d",&(x),&(y),&(z));
#define ALL(x) (x).begin(),(x).end()
#define tests int dsdsf;cin>>dsdsf;while(dsdsf--)
#define testss int dsdsf;CZ(dsdsf);while(dsdsf--)
using namespace std;
typedef pair<int,int> pii;
typedef vector<int> vi;
template<typename T,typename TT> ostream &operator<<(ostream &s,pair<T,TT> t) {return s<<"("<<t.first<<","<<t.second<<")";}
template<typename T> ostream &operator<<(ostream &s,vector<T> t){s<<"{";FOR(i,t.size())s<<t[i]<<(i==t.size()-1?"":",");return s<<"}"<<endl; }

#define MAXN 200003
#define LOGN 18

int ojc[MAXN],n,poz[MAXN],ile[MAXN];
int anc[MAXN][LOGN+1];
int root;

int licz_poz(int u)
{
    if (poz[u]==-1) 
        poz[u]=licz_poz(ojc[u])+1;
    return poz[u];
}

int LCA(int u,int v)
{
    if (poz[u]<poz[v]) return LCA(v,u);
    int roz=poz[u]-poz[v];
    REPD(k,LOGN,0)
        if ((1<<k)<=roz)
        {
            roz-=(1<<k);
            u=anc[u][k];
        }
    //juz sa na tym samym poziomie
    if (u==v) return u;
    REPD(k,LOGN,0)
        if (anc[u][k]!=anc[v][k])
        {
            u=anc[u][k];
            v=anc[v][k];
        }
    return ojc[u];
}


int get_dist(int u,int v)
{
	int w=LCA(u,v);
	return poz[u]-poz[w]+poz[v]-poz[w];
}


int main()
{
    ios_base::sync_with_stdio(0);
    cin>>n;
    root=0;
    REP(i,1,n-1)
    {
    	cin>>ojc[i];
    	ojc[i]--;
    }
    FOR(i,n) poz[i]=-1;
    poz[root]=0;
    FOR(i,n) if (poz[i]==-1) licz_poz(i);
    FOR(i,n) anc[i][0]=ojc[i];
    REP(i,1,LOGN) FOR(j,n) anc[j][i]=anc[anc[j][i-1]][i-1];
    int a=0,b=0;
    int aa,bb;
    int d=0;
    REP(i,1,n-1)
    {
    	aa=a;
    	bb=b;
    	if (get_dist(i,a)>d)
    	{
    		aa=a;
    		bb=i;
    		d=get_dist(i,a);
    	}
    	if (get_dist(i,b)>d)
    	{
    		aa=b;
    		bb=i;
    		d=get_dist(i,b);
    	}
    	a=aa;
    	b=bb;
    	cout<<d<<" ";
    }
    
    
    return 0;
}

