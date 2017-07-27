// 100 points by Roman Andreev
// OK, 0.740 sec, 5 mb

#include<cstdio>
#include<iostream>
#include<cmath>
#include<cstring>
#include<vector>
#include<algorithm>
#include<map>
#include<set>
#include<ctime>
#include<cassert>
#include <time.h>

#define maxN 100000

typedef int mas[maxN];

void Start( int n, mas a );
void Add( int i, int x );
void Del( int i );
int Get( int L, int R, int x );

const int maxn = 2 * maxN;

using namespace std;

#define y1 fndjifhwdn
#define ws vfsdkofsjd
#define fs first
#define sc second
#define pb push_back
#define mp make_pair

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pi;
int cnt;
const int MX=1500;
const int MXK=1300;
vector<vector<int> >v,vv;
void rebuild(){
	vector<int> v0;
	for (int i=0;i<(int)v.size();i++){
		for (int j=0;j<(int)v[i].size();j++){
			v0.pb(v[i][j]);
		}
	}
	v.clear();
	vv.clear();
	/*v.pb(v0);
	sort(v0.begin(),v0.end());
	vv.pb(v0);	*/
	vector<int> g;
	for (int i=0;i<(int)v0.size();i++){
		g.pb(v0[i]);
		if ((int)g.size()==MXK){
			v.pb(g);
			sort(g.begin(),g.end());
			vv.pb(g);
			g.clear();
		}
	}
	if ((int)g.size()>0){
		v.pb(g);
		sort(g.begin(),g.end());	
		vv.pb(g);
	}
}
void add1(int k,int x,int p){
	v[k].insert(v[k].begin()+p,x);
	vv[k].insert(lower_bound(vv[k].begin(),vv[k].end(),x),x);
}
void Add(int p,int x){
	int tk=0;
	assert(p>=0);
	bool chk=false;  
	for (int i=0;i<(int)v.size();i++){
		if (tk+(int)v[i].size()>=p){
			add1(i,x,p-tk);
			chk=true;
			break;
		} else 
			tk+=v[i].size();
	}
	assert(chk);
	cnt++;
	if (cnt%MX==0)
		rebuild();
}
void del1(int k,int p){
	int x=v[k][p];
	v[k].erase(v[k].begin()+p);	
	vv[k].erase(lower_bound(vv[k].begin(),vv[k].end(),x));
}
void Del(int p){
	assert(p>=0);
	int tk=0;
	bool chk=false;  
	for (int i=0;i<(int)v.size();i++){		
		if (tk+(int)v[i].size()>p){
			del1(i,p-tk);
			chk=true;
			break;
		} else 
			tk+=v[i].size();
	}
	assert(chk);
	cnt++;
	if (cnt%MX==0)
		rebuild();
}
int Get(int l,int r,int g){
	int ans=0;
	int tk=0;
	assert(l<=r && l>=0);
	for (int i=0;i<(int)v.size();i++){
		if (r<tk) return ans;
		if (l<=tk+(int)v[i].size()) {
			if (l<=tk && tk+(int)v[i].size()<=r){
				ans+=lower_bound(vv[i].begin(),vv[i].end(),g+1)-vv[i].begin();
			} else {
				for (int j=0;j<(int)v[i].size();j++) if (tk+j>=l && tk+j<=r){			
					if (v[i][j]<=g)
						ans++;
				}
			}
		}
		tk+=v[i].size();
	}
	assert(r<tk);
	return ans;
}
void Start( int n, mas a ){	
	cnt=0;
	v.clear();
	vv.clear();
	vector<int> v0;
	for (int i=0;i<n;i++){
		v0.pb(a[i]);
	}
	v.pb(v0);
	sort(v0.begin(),v0.end());
	vv.pb(v0);
	rebuild();
	return;
}

int main()
{
  static int n, a[maxn];
  long start = clock();
  int i;

  assert(freopen("kthstat.in", "r", stdin));
  assert(freopen("kthstat.out", "w", stdout));

  scanf("%d", &n);
  for (i = 0; i < n; i++)
    scanf("%d", &a[i]);

  Start(n, a);

  char type;
  int x, y, z, tn = 0;
  while (scanf(" %c", &type) == 1)
  {
    if (type == '+')
      scanf("%d%d", &x, &y), Add(x, y);
    else if (type == '-')
      scanf("%d", &x), Del(x);
    else if (type == '?')  
      scanf("%d%d%d", &x, &y, &z), printf("%d\n", Get(x, y, z));
    else
    {
      fprintf(stderr, "Unknown option: %c\n", type);
      exit(3128);
    }
    tn++;
  }
  fprintf(stderr, "OK, %d tests, time = %.2lf\n", tn, (double)(clock() - start) / CLOCKS_PER_SEC);
  return 0;
}
