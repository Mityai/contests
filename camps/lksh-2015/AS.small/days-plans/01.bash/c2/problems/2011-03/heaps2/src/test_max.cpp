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
  if(argc != 2)
  {
    fprintf(stderr,"Usage: <T>\n  T = type of the test\n");
    return 0;
  }
  get_test();
  int T = atoi(argv[1]);
  if (T == 1)
  {
    int k = 20;
    int m = (int)1e4;
    printf("%d\n", k);
    forn(i, k)
      printf("%d%c", i + 1, " \n"[i == k - 1]);
    printf("%d\n", m);
    forn(i, m)
      printf("%d%c", (int)1e6 - i, " \n"[i == m - 1]);
  }
  else if (T == 2)
  {
    int k = 20;
    int m = (int)1e4;
    printf("%d\n", k);
    forn(i, k)
      printf("%d%c", i * i + 1, " \n"[i == k - 1]);
    printf("%d\n", m);
    forn(i, m)
      printf("%d%c", (int)1e6, " \n"[i == m - 1]);
  }
  return 0;
}
