#include <iostream>
#include <fstream>
#include <sstream>

#include <vector>
#include <set>
#include <bitset>
#include <map>
#include <deque>
#include <string>

#include <algorithm>
#include <numeric>

#include <cstdio>
#include <cassert>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <cmath>

#define pb push_back
#define pbk pop_back
#define mp make_pair
#define fs first
#define sc second
#define all(x) (x).begin(), (x).end()
#define foreach(i, a) for (__typeof((a).begin()) i = (a).begin(); i != (a).end(); ++i)
#define len(a) ((int) (a).size())

#ifdef CUTEBMAING
#define eprintf(...) fprintf(stderr, __VA_ARGS__)
#else
#define eprintf(...) 42
#endif

using namespace std;

typedef long long int64;
typedef long double ld;
typedef unsigned long long lint;

const int inf = (1 << 30) - 1;
const int64 linf = (1ll << 62) - 1;
const int N = 1e6 + 100;
const int K = 150;
const int C = 20;

int n, q;
int a[N], b[N], c[N];
int reqa[N], reqb[N];
vector<int> g[N];

void readInfo() {
	cin >> n >> q;
	for (int i = 0; i < n - 1; i++) {
		scanf("%d%d%d", &a[i], &b[i], &c[i]);
		a[i]--, b[i]--;
		g[a[i]].pb(i), g[b[i]].pb(i);
		c[i] = min(c[i], n - 1);
		if (c[i] < 0) {
		    c[i] = n - 1;
		}
	}
	for (int i = 0; i < q; i++) {
		scanf("%d%d", &reqa[i], &reqb[i]);
		reqa[i]--, reqb[i]--;
	}
}

int cool[N], coolLen = 0;
int eu[N * 2], euLen = 0;
int in[N], out[N], curTime = 0;
int bin[N][C];
int ts[N], tsLen = 0;
int pos[N];
int parentEdge[N], parent[N];

inline bool anc(int u, int v) {
	return in[u] <= in[v] && out[v] <= out[u];
}

inline int lca(int u, int v) {
	if (anc(u, v)) {
		return u;
	}
	if (anc(v, u)) {
		return v;
	}
	for (int i = C - 1; i >= 0; i--) {
		if (bin[u][i] != -1 && !anc(bin[u][i], v)) {
			u = bin[u][i];
		}
	}
	assert(bin[u][0] != -1);
	return bin[u][0];
}

void dfsInfo(int v, int p = -1, int pe = -1) {
	parentEdge[v] = pe;
	parent[v] = p;
	bin[v][0] = p;
	eu[euLen++] = v;
	in[v] = curTime++;
	ts[pos[v] = tsLen++] = v;
	for (int i = 1; i < C; i++) {
		bin[v][i] = bin[v][i - 1] != -1 ? bin[bin[v][i - 1]][i - 1] : -1;
	}
	for (int e : g[v]) {
		int to = a[e] ^ b[e] ^ v;
		if (to != p) {
			dfsInfo(to, v, e);
			eu[euLen++] = v;
		}
	}
	out[v] = curTime++;
}

int nearest[N];

void buildNearest() {
	dfsInfo(0);
	for (int i = 0; i < K; i++) {
		cool[coolLen++] = rand() % n;
	}
	eprintf("coolLen = %d\n", coolLen);
	sort(cool, cool + coolLen);
	coolLen = unique(cool, cool + coolLen) - cool;
	static pair<int, int> dist[N];
	fill_n(dist, n, mp(inf, inf));
	deque<int> q;
	for (int i = 0; i < coolLen; i++) {
		dist[cool[i]] = mp(0, cool[i]);
		q.pb(cool[i]);
	}
	while (!q.empty()) {
		int v = q.front();
		q.pop_front();
		for (int e : g[v]) {
			int to = a[e] ^ b[e] ^ v;
			if (dist[to].fs > dist[v].fs + 1) {
				dist[to] = mp(dist[v].fs + 1, dist[v].sc);
				q.pb(to);
			}
		}
	}
	for (int i = 0; i < n; i++) {
		nearest[i] = dist[i].sc;
	}
}

struct mexstruct {
	int val[N];
	bool rmq[N * 4 + 100];
	int maxn = 1;

	void clear() {
		maxn = 1;
		while (maxn < n) {
			maxn *= 2;
		}
		fill_n(val, n, 0);
		fill_n(rmq, maxn * 2, false);
	}

	int value() {
		int i = 1;
		assert(!rmq[1]);
		while (i < maxn) {
			if (!rmq[i * 2]) {
				i = i * 2;
			} else {
				i = i * 2 + 1;
			}
		}
		return i - maxn;
	}

	void add(int x, int d) {
		int i = x + maxn;
		val[x] += d;
		rmq[i] = val[x] > 0;
 		for (i >>= 1; i; i >>= 1) {
			bool val = rmq[i * 2] & rmq[i * 2 + 1];
			if (rmq[i] == val) {
				break;
			} else {
				rmq[i] = val;
			}
		}
	}
};

struct coolstruct {
	mexstruct mex;
	bool used[N];

	inline void add(int e) {
		if (!used[e]) {
			used[e] = true;
			mex.add(c[e], 1);
		} else {
			used[e] = false;
			mex.add(c[e], -1);
		}
	}

	inline void clear() {
		mex.clear();
		fill_n(used, n, 0);
	}

	inline void xorToLca(int u, int l) {
		while (u != l) {
			add(parentEdge[u]);
			u = parent[u];
		}
	}

	inline void xorPath(int u, int v) {
		int l = lca(u, v);
		xorToLca(u, l);
		xorToLca(v, l);
	}

	inline int getCount() {
		return mex.value();
	}
};

struct cmp {
	int s;

	cmp(int s) {
		this->s = s;
	}

	inline int pos(int v) {
		int res = ::pos[v] - s;
		if (res < 0) {
			res += n;
		}
		return res;
	}

	inline bool operator () (int a, int b) {
		return pos(reqa[a]) < pos(reqa[b]);
	}
};

vector<int> req[N];
coolstruct st;
int ans[N];

void answerQueries(int v) {
	st.clear();
	int curU = v, curV = v;
	sort(all(req[v]), cmp(pos[v]));
	for (int r : req[v]) {
		st.xorPath(curU, reqa[r]);
		st.xorPath(curV, reqb[r]);
		curU = reqa[r];
		curV = reqb[r];
		ans[r] = st.getCount();
	}
}

void answerQueries() {
	for (int i = 0; i < q; i++) {
		req[nearest[reqb[i]]].pb(i);
	}
	for (int i = 0; i < n; i++) {
		if (len(req[i]) > 0) {
			static int cur = 0;
			answerQueries(i);
		}
	}
}

void writeAnswer() {
	for (int i = 0; i < q; i++) {
		printf("%d\n", ans[i]);
	}
}

int main() {
	readInfo();
	buildNearest();
	answerQueries();
	writeAnswer();
    return 0;
}
