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
#include <ctime>
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
#include "testlib.h"
using namespace std;
typedef pair<int,int> pii;
typedef vector<int> vi;
template<typename T,typename TT> ostream &operator<<(ostream &s,pair<T,TT> t) {return s<<"("<<t.first<<","<<t.second<<")";}
template<typename T> ostream &operator<<(ostream &s,vector<T> t){s<<"{";FOR(i,t.size())s<<t[i]<<(i==t.size()-1?"":",");return s<<"}"<<endl; }

int p[200000];
int szuk(int x){if (x==p[x]) return x;return p[x]=szuk(p[x]);}
inline void unia(int x,int y){p[szuk(x)]=szuk(y);}

void path(int n)
{
	cout<<n<<"\n";
	FOR(i,n-1)
	{
		cout<<i+1<<"\n";
	}
}


void binary(int n)
{
	cout<<n<<"\n";
	REP(i,2,n) 
	{
		cout<<i/2<<"\n";
	}
}

void rand_long(int n1,int n2)
{
	int n=n1+n2;
	cout<<n<<"\n";
	REP(i,2,n1)
	{
		cout<<rnd.next(1,i-1)<<"\n";
	}
	REP(i,n1+1,n)
	{
		cout<<i-1<<"\n";
	}
}

void rand_last(int n,int k)
{
	cout<<n<<"\n";
	REP(i,2,n)
	{
		int par=rnd.next(max(1,i-k),i-1);
		cout<<par<<"\n";
	}
}


void rand_tree(int n)
{
	cout<<n<<"\n";
	REP(i,2,n) cout<<rnd.next(1,i-1)<<"\n";
}

int main(int argc, char* argv[])
{
    ios_base::sync_with_stdio(0);
    if (argc<2) return 1;
    int param=atoi(argv[1]);
    rnd.setSeed(param);
    if (param==1) path(2);
    if (param==2) rand_tree(3);
    if (param==3) rand_tree(10);
    if (param==4) rand_tree(1000);
    if (param==5) rand_tree(180000);
    if (param==6) binary(120);
    if (param==7) binary(159999);
    if (param==8) path(98989);
    if (param==9) rand_long(100,10000);
    if (param==10) rand_long(99999,50001);
    if (param==11) rand_long(10000,188001);
    if (param==12) rand_last(1000,8);
    if (param==13) rand_last(10000,2);
    if (param==14) rand_last(200000,3);
    if (param==15) rand_last(200000,10);
    if (param>15) rand_last(200000,100);



	return 0;
}

