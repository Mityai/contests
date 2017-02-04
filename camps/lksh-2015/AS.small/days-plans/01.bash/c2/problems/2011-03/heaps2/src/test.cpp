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
#define forn(i,n) for(int i=0;i<(int)n;i++)
#define taskname ""
#include"random.h"
typedef long long ll;

using namespace std;
void get_test()
{
  int test=0;
  char str[100];
  do
  {
    fclose(stdin);
    test++;
    sprintf(str,"%02d",test);
  }while(freopen(str,"r",stdin)!=NULL);
  freopen(str,"w",stdout);
  initrand(test);
}
const int N=1000000;
const int M=10000;
const int K=20;
int main(int argc,char *argv[])         
{
  if(argc != 4)
  {
    fprintf(stderr,"The first parametr is maxN. The second parametr is the number of tests. The third number is the number of steps\nDefault value is 0.\n");
    return 0;
  }
  get_test();
  int mxn = atoi(argv[1]);
  int mxm = atoi(argv[2]);
  int mxs = atoi(argv[3]);
  if(mxn == 0) mxn = N;
  if(mxm == 0) mxm = M;
  if(mxs == 0) mxs = K;
  int s=(int)rndLong(mxs)+1;
  printf("%d\n",s);
  forn(i,s)
    printf("%d%c",(int)rndLong(mxn)+1," \n"[i==s-1]);
  int m=(int)rndLong(mxm)+1;
  printf("%d\n",m);
  forn(i,m)
    printf("%d%c",(int)rndLong(mxn)+1," \n"[i==m-1]);
    
  return 0;
}
