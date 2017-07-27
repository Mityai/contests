#include <cstdio>
#include <cstdlib>
#include <vector>
#include <iostream>
#include <algorithm>
#include<map>
#include<cmath>
#include<string>
#include <cstring>
#include <set>
#include <queue>
#include <stack>
using namespace std;
typedef unsigned long long u64;
typedef long long i64;
typedef long long ll;
const int INF=(1U<<31)-1;
#define REP(i,n) for(int i=0;i<(n);i++)
#define FOR(i,a,b) for(int i=(a);i<(b);i++)
#define FORD(i,a,b) for(int i=(a);i>(b);i--)

const double eps=1e-8;
const int val=3;

char buf[100000];
int nextint()
{
    int t;
    if(scanf("%d",&t)!=1) exit(0);
    return t;
}

int res=0;
vector<vector<int> > v;
vector<int> a;
vector<int> b;
vector<int> used;
queue<int> free_in, free_out;
int n;

void dfs(int cur)
{
 if(used[cur]) return;
 used[cur]=1;
 if(cur<n)
  free_in.push(cur);
 else
  free_out.push(cur-n);
 while(!free_in.empty()&&!free_out.empty())
 {
  int inid=free_in.front();
  int outid=free_out.front();
  int val=min(a[inid],b[outid]);
  a[inid]-=val;
  b[outid]-=val;
  res+=val;
  if(a[inid]==0) free_in.pop();
  if(b[outid]==0) free_out.pop();
 }
 REP(i,v[cur].size())
  dfs(v[cur][i]);
}

int main()
{
 n=nextint();
 int m=nextint();
 v.resize(2*n);
 used.resize(2*n);
 REP(i,n) a.push_back(nextint());
 REP(i,n) b.push_back(nextint());
 REP(i,m)
 {
  int a=nextint()-1;
  int b=nextint()-1+n;
  v[a].push_back(b);
  v[b].push_back(a);
 }
 REP(i,n)
 {
  if(!used[i])
  {
   dfs(i);
  }
  while(!free_in.empty()) free_in.pop();
  while(!free_out.empty()) free_out.pop();
 }
 printf("%d\n",res);
 return 0;
}