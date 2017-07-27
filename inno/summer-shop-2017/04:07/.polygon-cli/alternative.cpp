#include"vector"
#include"stdio.h"
#include"iostream"
#include"cassert"
using namespace std;
#define INF 1000000000

template <typename T, void (*merge)(T&, const T&), T id, int minidx=1, bool rev=0>
struct BIT {
    int N;
    T* merged;
    BIT(){N=-1;}
    void init(int n) {
        if(N+1) delete[] merged;
        N = n;
        merged = new T[N+1];
        merged[0] = id;
        for(int i=N; i; i--) merged[i] = id;
    }
    ~BIT() { if(N+1) delete[] merged; }
    void update(int p, T val) {
        if(rev) p = N - p + minidx; else p -= minidx-1;
        assert(p>0);
        while(p<=N) merge(merged[p], val), p += p&-p;
    }
    T read(int p) {
        if(rev) p = N - p + minidx; else p -= minidx-1;
        if(p<=0) return merged[0];
        assert(p<=N);
        T ret = merged[0];
        while(p) merge(ret, merged[p]), p -= p&-p;
        return ret;
    }
};

void maxmerge(int& i, const int& j) { if(i<j)i=j; }
void summerge(int& i, const int& j) { i+=j; }
typedef int* Pint;

struct edge {
    int v;
    edge(int x):v(x){}
};


class dynamic_tree {
    struct Others {
        int ht[2], node;
        Others() {init(0);}
        void init(int x) { ht[0] = ht[1] = x; node = -1; }
        void update(int n, int h) {
            if(h>ht[0]) { 
                if(node!=n) ht[1] = ht[0], node = n;
                ht[0] = h;
            }
            else if(h>ht[1]) ht[1] = h;
        }
        int best(int n) {    return n==node?ht[1]:ht[0];    }
    };
    struct path {
        int head, parent_idx, len;
        BIT<int, maxmerge, -INF, 0> otherslookup;  // depth of deepest descendant not along - 2 * depth of myself
        BIT<int, maxmerge, -INF, 0, 1> pathlookup; // depth of deepest descendant along path.
        void init() {
            otherslookup.init(len);
            pathlookup.init(len);
        }
        path(int hd=0, int p=-1, int l=0) {
            head = hd, parent_idx = p, len = l;
        }
        inline int myidx(const int* hts, const int me) {
            return hts[me]-hts[head];
        }
    };
    vector<edge>* G;
    Pint hts, path_idx, max_depth; // depth of two deepest descendants among non path one
    Others* others;
    vector<path*> paths;
    void init_dfs(int u, int p, int h) {
        hts[u] = h;
        max_depth[u] = 0;
        vector<edge>::iterator it;
        for(it =G[u].begin();it!=G[u].end();it++)
            if(it->v!=p) {
                init_dfs(it->v, u, h+1);
                maxmerge(max_depth[u], max_depth[it->v]);
            }
        max_depth[u]++;
    }
    void decomp(int cur, int p, int idx) {
        path_idx[cur] = idx;
        paths[idx]->len++;
        int best_child = -1;
        vector<edge>::iterator it;
        for(it=G[cur].begin();it!=G[cur].end();it++) {
            if(it->v==p) continue;
            if(best_child == -1 or max_depth[best_child] < max_depth[it->v])
                best_child = it->v;
        }
        if(best_child==-1)
            paths[idx]->init();
        for(it=G[cur].begin();it!=G[cur].end();it++)  {
            if(it->v==p) continue;
            int pth = idx;
            if(best_child != it->v)
                pth = paths.size(), paths.push_back(new path(it->v, cur));
            decomp(it->v, cur, pth);
        }
    }
    public:
    int diameter;
    dynamic_tree(int root, int n, vector<edge> G[]) {
        hts = new int[n];
        path_idx = new int[n];
        max_depth = new int[n];
        others = new Others[n];
        paths.clear();
        this->G = G;
        init_dfs(root, -1, 0);
        paths.push_back(new path(root));
        decomp(root, -1, 0);
        delete[] max_depth;
        diameter = 0;
        others[root].init(hts[root]);
        path& p = *paths[path_idx[root]];
        p.otherslookup.update(0, -hts[root]);
        //p.pathlookup.update  (-1, hts[root]);
    }
    void put_vertex(int v) {
        //update all ancestors, at the same time query most distant vertex
        const int myht = hts[v];
        path& pp = *paths[path_idx[v]];
        int me = pp.parent_idx, cld = pp.head, idx = pp.myidx(hts, v);
        int ans = pp.otherslookup.read(idx)+myht;
        bool good = (pp.pathlookup.read(0)<myht) and (others[pp.head].ht[0]<myht);
        others[v].init(hts[v]);
        pp.otherslookup.update(idx,  -myht);
        pp.pathlookup.update  (idx-1, myht);
        while(good and me>=0) {
            path& p = *paths[path_idx[me]];
            idx = p.myidx(hts, me);
            if(idx) maxmerge(ans, p.otherslookup.read(idx-1)+myht);
            //printf("x %d\n",p.otherslookup.read(idx-1));
            maxmerge(ans, p.pathlookup.read(idx)+myht-2*hts[me]);
            //printf("y %d\n",p.pathlookup.read(idx));
            maxmerge(ans, others[me].best(cld)+myht-2*hts[me]);
            //printf("z %d\n", others[me].best(cld));
            good = (p.pathlookup.read(0)<myht) and (others[p.head].ht[0]<myht);
            p.otherslookup.update(idx, myht-2*hts[me]);
            p.pathlookup.update  (idx-1, myht);
            others[me].update(cld, myht);
            me = p.parent_idx;
            cld = p.head;
        }
        maxmerge(diameter, ans);
    }
};

vector<edge>* G;
int n;
void read_graph() {
    n= 0;
    scanf("%d", &n);
    if(n==1)fprintf(stderr, "got one :D\n");
    G = new vector<edge> [n];
    assert(n>0 and n<=200000);
    for(int i=1; i<n ; i++) {
        int x;
        scanf("%d", &x);
        assert(x>0 and x<=i);
        G[x-1].push_back(edge(i));
    }
}
int dia=-INF;
int solve(int upper, int root) {
    assert(upper>root);
    int m=0;
    vector<edge>::iterator it;
    for(it=G[root].begin();it!=G[root].end();it++) 
    {
        if(it->v >=upper) continue;
        int dp = solve(upper, it->v)+1;
        maxmerge(dia,dp+m);
        maxmerge(m, dp);
    }
    return m;
}
void slv() {
    read_graph();
    dynamic_tree t(0, n, G);
    for(int i=1; i<n; i++) {
//        solve(i+1, 0);
        t.put_vertex(i);
        assert(t.diameter<=i);
//        assert(t.diameter==dia);
        printf("%d ", t.diameter);
    }
}
int main() {
    slv();
}