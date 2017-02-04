#include<cassert>
#include<queue>
#include<cstring>
#include<cstdio>
#include<vector>
#include<string>
#include<set>
#include<map>
#include<cmath>
#include<iostream>
#include<algorithm>

#define forn(i,n) for(int i=0;i<(int)(n);i++)
#define taskname "heaps2"
#define deb(x) cerr<<#x<<'='<<(x)<<endl
typedef long long ll;

using namespace std;

const int N=1000000;
const int M=10000;
const int K=20;

bool ans[N+1];
int k;
int x[K];

int main()
{
  assert(freopen(taskname".in","r",stdin));
  assert(freopen(taskname".out","w",stdout));
  int m; 
  scanf("%d",&k);
  assert( k>0 && k<=K);
  forn(i,k)
  {
    scanf("%d",&x[i]);
    assert(x[i]>0 && x[i]<=N);
  }
  
  forn(i,N+1)
  {
    forn(j,k)
      if((i>=x[j])&&(!ans[i-x[j]]))
        ans[i]=true;
  }
  scanf("%d",&m);
  assert(m>0 && m<=M);
  forn(i,m)
  {
    int a;
    assert(scanf("%d ",&a) == 1);
    assert(a>0 && a<=N);
    puts(ans[a]?"First":"Second");
  }
  assert(scanf("%*d")!=1);
  return 0;
}

