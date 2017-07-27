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
  vector<int> data,sorted;
};
const int PIECE_SIZE = 320,MAXCOUNT = 2000;
tree tmas[MAXCOUNT + 100];
vector<int> makeVector(vector<int>::iterator a,vector<int>::iterator b){
  vector<int> ans;
  while(a != b){ 
    ans.push_back(*a);
    a++;
  }
  return ans;
}
int sz = 0;
tree* newTree(vector<int> data){
  assert(sz < MAXCOUNT + 100);
  tree *t = tmas + sz++;
//  tree *t = new tree();
  //sz++;
  t->next = t->prev = NULL;
  t->data = t->sorted = data;
  t->isSeted = t->isReversed = false;
  t->X = -1;
  sort(t->sorted.begin(),t->sorted.end());
  return t;
}

void down(tree *t){
  if(t->isReversed)
    reverse(t->data.begin(),t->data.end());
  if(t->isSeted)
    forn(i,t->data.size()) 
      t->data[i] = t->sorted[i] = t->X;
  t->isSeted = t->isReversed = false;
}

void cut(tree *t,int num,tree **l, tree **r){
  *l = newTree(makeVector(t->data.begin(), t->data.begin() + num ));
  *r = newTree(makeVector(t->data.begin()+num, t->data.end()));
}

void merge(tree *l,tree *r){
  l->next = r;
  r->prev = l;
}

void split(tree *t,int num,tree **l,tree **r)
{
  if((int)t->data.size() < num)
    split(t->next,num - t->data.size(),l,r);
  else if((int)t->data.size() == num){
    *l = t;
    *r = t->next;
  }
  else{
    down(t);
    cut(t, num, l, r);
    merge(t->prev, *l);
    merge(*l, *r);
    merge(*r, t->next); 
    t->data.resize(0);
    t->sorted.resize(0);
  }
}
tree* root;
vector<int> out(tree *t, bool fl = false){ 
  vector<int> ans;
  while(t != NULL){
    down(t);
    if(fl)
      eprintf("%d\n",t->data.size());
    forn(i,t->data.size()){
      ans.push_back(t->data[i]);
      if(fl)
        eprintf("out %d\n",t->data[i]);
    }
    if(fl) 
      eprintf("\n");
    t = t->next;
  }
  return ans;
}
int n;
vector<int> mas;
void build(){
  int sqr = PIECE_SIZE;
  //eprintf("Rebuild\n");
  root = newTree(vector<int> ());
  tree *last = root;
  forn(i, (n + sqr - 1) / sqr){
    tree *t = newTree(makeVector(mas.begin() + i*sqr,mas.begin() + min((i+1)*(sqr),n)));
    merge(last, t);
    last = t;
  }
  merge(last,newTree(vector<int> ()));
}
int main()         
{
  #define taskname "sqrtrev"
  assert(freopen(taskname".in","r",stdin));
  assert(freopen(taskname".out","w",stdout));
  scanf("%d",&n);
  #ifdef DEBUG
  int t = clock();
  #endif
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
      sz = 0;
      build();
    } 
    tree *a,*b,*c,*d;
    split(root,l - 1,&a,&b);
    split(root,r, &c, &d);
    b = a->next;
    if(!strcmp(str,"get")){
      int ans = 0;
      scanf("%d",&x);
      while(b != d){
        if(b-> isSeted)
          ans += (x <= b->X)*b->data.size();
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
  #ifdef DEBUG
  eprintf("%.2lf",(clock()-t)/(double)CLOCKS_PER_SEC)
  #endif
  return 0;
}

