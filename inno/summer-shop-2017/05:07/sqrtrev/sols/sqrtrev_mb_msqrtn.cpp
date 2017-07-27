#include<cassert>
#include<ctime>
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

struct tree{
  tree *next,*prev;
  bool isSeted,isReversed;
  int X;
  int l,r;
  vector<int> sorted;
};
const int PIECE_SIZE = 1020,MAXCOUNT = 3000;
tree tmas[MAXCOUNT + 100];
vector<int> mas;
int sz = 0;
tree* newTree(int l,int r){
  assert(sz < MAXCOUNT + 100);
//  tree *t = tmas + sz++;
  tree *t = new tree();
  sz++;
  t->next = t->prev = NULL;
  t-> l = l;
  t-> r = r;
  assert(l <= r);
  t->sorted.resize(r - l);
  for(int i = l ; i < r; i++)
    t->sorted[i-l] = mas[i];
  t->isSeted = t->isReversed = false;
  t->X = -1;
  sort(t->sorted.begin(),t->sorted.end());
  return t;
}

void down(tree *t){
  if(t->isReversed)
    reverse(mas.begin() + t->l,mas.begin() + t->r);
  if(t->isSeted)
    forn(i, t->r - t->l) 
       mas[t->l + i] = t->sorted[i] = t->X;
  t->isSeted = t->isReversed = false;
}

void cut(tree *t,int num,tree **l, tree **r){
  *l = newTree(t->l,t->l + num);
  *r = newTree(t->l + num, t->r);
}

void merge(tree *l,tree *r){
  l->next = r;
  r->prev = l;
}

void split(tree *t,int num,tree **l,tree **r)
{
  if((int)t->r-t->l < num)
    split(t->next,num - t->r + t->l,l,r);
  else if((int)t->r-t->l == num){
    *l = t;
    *r = t->next;
  }
  else{
    down(t);
    cut(t, num, l, r);
    merge(t->prev, *l);
    merge(*l, *r);
    merge(*r, t->next); 
    t->sorted.resize(0);
  }
}
int n;
tree* root;
vector<int> out(tree *t, bool fl = false){ 
  vector<int> ans;
  if(fl)
  eprintf("sizes: ");
  ans.resize(n);
  int ans_sz = 0;
  while(t != NULL){
    down(t);
    for(int i = t->l;i< t->r;i++)
      ans[ans_sz++] = (mas[i]);
    if(fl)
      eprintf("%d ",t->r - t->l);
    t = t->next;
  }
  if(fl){
  eprintf("\n");
  forn(i,mas.size())
    eprintf("%d ",mas[i]);
  eprintf("\n");
  }
  return ans;
}
void build(){
  int sqr = PIECE_SIZE;
  root = newTree(0,0);
  tree *last = root;
  forn(i, (n + sqr - 1) / sqr){
    tree *t = newTree(i*sqr, min((i+1)*(sqr),n));
    //eprintf("%d %d\n",t->l,t->r);
    merge(last, t);
    last = t;
  }
  merge(last,newTree(0,0));
}
int main()         
{
  #define taskname "sqrtrev"
  assert(freopen(taskname".in","r",stdin));
  assert(freopen(taskname".out","w",stdout));
  #ifdef DEBUG
  int t = clock();
  #endif

  scanf("%d",&n);
  mas = vector<int>(n);
  forn(i,n)
    scanf("%d ",&mas[i]);
  build();
  int m;
  scanf("%d ",&m);
  char str[100];
  forn(i,m){
    int l,r,x;
    scanf(" %s %d %d",str,&l,&r);
    if(sz > MAXCOUNT){
      //eprintf("%d\n",sz);
      mas = out(root);
      out(root);
      sz = 0;
      build();
    } 
    tree *a,*b,*c,*d;
    split(root,l - 1,&a,&b);
    split(root,r, &c, &d);
    //out(root, true);
    b = a->next;
    if(!strcmp(str,"get")){
      int ans = 0;
      scanf("%d",&x);
      while(b != d){
        if(b-> isSeted)
          ans += (x <= b->X)*(b->r-b->l);
        else{
          ans += b->sorted.end()-lower_bound(b->sorted.begin(),b->sorted.end(),x);
          //eprintf("cnt = %d\n",b->sorted.end()-lower_bound(b->sorted.begin(),b->sorted.end(),x));
        }
        b = b->next;
      }
      printf("%d\n",ans);
    }
    else if(!strcmp(str,"set")){
      scanf("%d",&x);
      while(b != d){
        b->isSeted = true;
        b->X = x;
        b = b->next;
      }
    }
    else if(!strcmp(str,"reverse")){
      vector<tree *> mas;
      while(b != d){
        mas.push_back(b);
        b -> isReversed ^= true;
        b = b->next;
      }
      reverse(mas.begin(), mas.end());
      merge(a,mas[0]);
      forn(j, mas.size() - 1)
        merge(mas[j], mas[j+1]);
      merge(mas[mas.size()-1], d);
    }
  }          
/*
  mas = out(root);
  forn(i,n)
    printf("%d ",mas[i]);
*/

  #ifdef DEBUG
  eprintf("%.2lf",(clock()-t)/(double)CLOCKS_PER_SEC)
  #endif
  return 0;
}

