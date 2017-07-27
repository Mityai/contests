#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <cmath>
#include <cassert>
#include <ctime>
#include <algorithm>
#include <queue>
#include <memory.h>
#include <stack>
#define mp make_pair
#define pb push_back                     
#define setval(a,v) memset(a,v,sizeof(a))

#if ( _WIN32 || __WIN32__ )
    #define LLD "%I64d"
#else
    #define LLD "%lld"
#endif

using namespace std;

typedef long long int64;
typedef long double ld;

const int MAXN = 210000;
const int MAXLOG = 20;

int p[MAXN];
int rank[MAXN];
int anc[MAXN];
int up[MAXN][MAXLOG];
int h[MAXN];

int create(){
    static int cnt = 0;
    p[cnt] = cnt;
    rank[cnt] = 1;
    anc[cnt] = cnt;
    return cnt++;
}

int root(int v){
    if (v == p[v])
        return v;
    return p[v] = root(p[v]);
}

void merge(int v,int u){
    v = root(v);
    u = root(u);

    if (rank[v] > rank[u])
        swap(v,u);

    p[v] = u;
    anc[u] = min(anc[v],anc[u]);

    if (rank[v] == rank[u])
        rank[u]++;
}

void add(int v){
    int nv = create();
    up[nv][0] = v;
    for (int i = 1; i < MAXLOG;i++)
        up[nv][i] = up[up[nv][i-1]][i-1];
    h[nv] = h[v] + 1;
}

void erase(int v){
    merge(v,up[v][0]);
}

int uph(int x,int h){
    for (int i = MAXLOG - 1; i >= 0; --i)
        if (h & (1<<i))
            x = up[x][i];
    return x;
}

int lca(int v,int u){
    if (h[v] > h[u])
        swap(v,u);
    u = uph(u,h[u] - h[v]);
    if (v == u)
        return v;
    for (int i = MAXLOG -1; i >= 0; --i)
        if (up[v][i] != up[u][i]){
            v = up[v][i];
            u = up[u][i];
        }
    return up[u][0];
}

int solve(int v,int u){
    return anc[root(lca(v,u))];
}

int main(){
    freopen("carno.in","r",stdin);
    freopen("carno.out","w",stdout);
    create();
    int m;
    scanf("%d",&m);
    for (int i = 0; i < m; i++){
        int u,v;
        if (scanf(" + %d", &u) == 1)
            add(u-1);
        else if (scanf(" - %d", &u) == 1)
            erase(u-1);
        else {
            scanf("? %d %d ", &u, &v);
            printf("%d\n", solve(v-1,u-1) + 1);
        }
    }
    return 0;
}