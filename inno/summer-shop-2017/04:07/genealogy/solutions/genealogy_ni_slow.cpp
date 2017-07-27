#include <iostream>
#include <cassert>
#include <cmath>
#include <string>
#include <cstring>
#include <vector>
#include <fstream>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <set>
#include <map>
#include <iomanip>
#define nextLine() { for (int c = getchar(); c != '\n' && c != EOF; c = getchar()); }
#define sqr(a) ((a)*(a))
#define has(mask,i) (((mask) & (1<<(i))) == 0 ? false : true)
#define eprintf(...) fprintf(stderr, __VA_ARGS__)
#define task "genealogy"
using namespace std;

#define pii pair<int,int>
#define mp make_pair
#define pb push_back
#define fi first
#define se second

#if ( _WIN32 || __WIN32__ )
    #define LLD "%I64d"
#else
    #define LLD "%lld"
#endif

typedef long long LL;
typedef long double ldb;

const int inf = (1 << 30) - 1;
const ldb eps = 1e-9;
const ldb pi = fabs(atan2(0.0, -1.0));
const int maxn = 100005;

int n;
int par[maxn];
void load()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf("%d", &par[i]);
}

bool mark[maxn];
void solve()
{
	int q;
	scanf("%d", &q);
	for (int i = 0; i < q; i++)
	{
		int k;
		scanf("%d", &k);
		memset(mark, false, sizeof(mark));
		int cnt = 0;
		for (int j = 0; j < k; j++)
		{
			int v;
			scanf("%d", &v);
			for (; v != -1 && !mark[v]; v = par[v])
			{
				mark[v] = true;
				cnt++;
			}
		}
		printf("%d\n", cnt);
	}
}

int main()
{
	freopen(task".in","r",stdin);
	freopen(task".out","w",stdout);
	load();
	solve();
	return 0;
}
