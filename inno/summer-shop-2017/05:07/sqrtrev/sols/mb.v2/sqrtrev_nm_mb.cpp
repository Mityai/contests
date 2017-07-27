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
#define eprintf(...) {fprintf(stderr, __VA_ARGS__);fflush(stderr);}

#define eps 1e-12

#define sqr(a) ((a)*(a))
#define mp(a,b) make_pair(a,b) 
#define forn(i,n) for(int i=0;i<(int)n;i++)
#ifdef DEBUG
#define deb(x) cerr<<#x<<'='<<x<<endl
#else
#define deb(x) 
#endif
typedef long long ll;

using namespace std;

void belong(int a,int l,int r){ assert(l<=a && a<=r);}
const int N = (int)1e5;
int mas[N];

int main()         
{
  #define taskname "sqrtrev"
  assert(freopen(taskname".in","r",stdin));
  assert(freopen(taskname".out","w",stdout));
  
  int n,m;
  assert(scanf("%d", &n) == 1);
  belong(n,1,N);
  forn(i, n)
    assert( scanf("%d",&mas[i]) == 1);
  
  assert(scanf("%d ", &m) == 1);
  belong(m,1,N);
  
  char str[100];
  int l,r,x;
  forn(i, m){
    //deb(scanf(" %s %d %d",str,&l,&r));
    assert(scanf(" %s %d %d",str,&l,&r) == 3);
    belong(l,1,n);
    belong(r,l,n);
    if(!strcmp("get",str)){
      assert(scanf("%d ", &x) == 1);
      int ans = 0;
      for(int i = l - 1;i < r;i++)
        if(mas[i]>= x)
          ans++;
      printf("%d\n",ans);
    }
    else if(!strcmp("set",str)){
      assert(scanf("%d ",&x) == 1);
      for(int i = l - 1; i < r;i++)
        mas[i] = x;
    }
    else if(!strcmp("reverse",str))
      reverse(mas + l - 1,mas + r );
    else
      assert(0);
  }
  forn(i,n)
    printf("%d ",mas[i]);

  return 0;
}

