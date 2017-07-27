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

const int N = 100000;
int rnd(){
  return rand()<<15 | rand();
}
char *types[3] = {"reverse","get","set"};
int rdtsc(){
  asm("rdtsc");
}
int main()         
{
  srand(rdtsc());
//  int n = rnd()%N + 1, m = rnd()%N +1;
  int n = N,m=N;
  printf("%d\n",n);
  forn(i,n)
    printf("%d ",rnd());
  printf("\n%d\n",m);
  forn(i,m){
    int type = rnd()%3;
    int l = rnd()%n + 1,r = rnd()%n + 1;
    if(l > r)
      swap(l,r);
    printf("%s %d %d ",types[type],l,r);
    if(type != 0)
      printf("%d",rnd());
    puts("");
  }
  return 0;
}

