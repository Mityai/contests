#include "bits/stdc++.h"
#define puba push_back
#define mapa make_pair
#define ff first
#define ss second
#define bend(_x) (_x).begin(), (_x).end()
#define szof(_x) ((int) (_x).size())
#define TASK_NAME ""

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
const int MAXN = 1e5 + 5, bd = 18;
const int SQRT = 100;
const int SQRT2 = 333;

int n, q;
int binup[bd][MAXN];
vector<pii> graph[MAXN];
int valueup[MAXN];
//int have[MAXN];
int depth[MAXN];
int tin[MAXN];
int tcounter;

//vector<int> arrx;

int dfs(int v, int p, int d, int val) {
	//valueup[v] = lower_bound(bend(arrx), val) - arrx.begin();
	valueup[v] = min(val, MAXN - 1);
	tin[v] = tcounter++;
 	depth[v] = d;
 	binup[0][v] = p;
 	for (int i = 1; i < bd; ++i) {
 	 	binup[i][v] = binup[i - 1][binup[i - 1][v]];
 	}
 	for (pii to: graph[v]) {
 	 	if (to.ff != p) {
 	 	 	dfs(to.ff, v, d + 1, to.ss);
 	 	}
 	}
 	return 0;
}

int myrand() {
 	return (rand() << 15) + rand();
}

int chosen[MAXN];

int get_lca(int a, int b) {
	if (depth[a] > depth[b]) {
	 	swap(a, b);
	}
	for (int i = bd - 1; i >= 0; --i) {
	 	if (depth[a] + (1 << i) <= depth[b]) {
	 	 	b = binup[i][b];
	 	}
	}
	if (a == b) {
	 	return a;
	}
	for (int i = bd - 1; i >= 0; --i) {
	 	if (binup[i][a] != binup[i][b]) {
	 	 	a = binup[i][a];
	 	 	b = binup[i][b];
	 	}
	}
	return binup[0][a];
}

int have[MAXN];
int chunk[MAXN];

int add(int num) {
 	have[num]++;
	if (have[num] == 1) {
	    chunk[num / SQRT2]++;
	}	
	return 0;
}

int rem(int num) {
 	have[num]--;
	if (have[num] == 0) {
	    chunk[num / SQRT2]--;
	}	
	return 0;
}


int cond[MAXN];

int revert(int v) {
 	if (cond[v]) {
 	 	add(valueup[v]);
 	} else {
 	 	rem(valueup[v]);
 	}
 	cond[v] ^= 1;
 	return 0;
}

int get_ans() {
 	for (int i = 0; i < MAXN; ++i) {
 	 	if (chunk[i] != SQRT2) {
 	 	 	for (int j = 0; j < SQRT2; ++j) {
 	 	 	 	if (!have[i * SQRT2 + j]) {
 	 	 	 	 	return i * SQRT2 + j;
 	 	 	 	}
 	 	 	}
 	 	}
 	}
 	return MAXN;
}

int main() {
	//cerr << RAND_MAX << endl;
	//freopen("inp", "r", stdin);
	//freopen(TASK_NAME ".out", "w", stdout);

	scanf("%d%d", &n, &q);
	
	for (int i = 0; i < n - 1; ++i) {
	 	int u, v, x;
	 	scanf("%d%d%d", &u, &v, &x);
	 	--u; --v;
	 	graph[u].puba({v, x});
	 	graph[v].puba({u, x});
	 	//arrx.puba(x);
	}

	for (int i = 0; i < n; ++i) {
	 	random_shuffle(bend(graph[i]));
	}

	dfs(0, 0, 0, 0);

	
	vector<int> nearest;
	{
		int c = 0;
		vector<int> dist;
		nearest.resize(n);
		dist.resize(n);
	 	queue<pii> qu;
	 	qu.push({0, -1});
	 	while (szof(qu)) {
	 	 	pii p = qu.front();
	 	 	qu.pop();
	 	 	//cerr << p.ff << " " << dist[p.ff] << endl;
	 	 	if (dist[p.ff] % SQRT == 0) {
	 	 	 	chosen[p.ff] = true;
	 	 	 	nearest[p.ff] = p.ff;
	 	 	 	++c;
	 	 	}
	 	 	for (pii to: graph[p.ff]) {
	 	 	 	if (to.ff != p.ss) {
	 	 	 		nearest[to.ff] = nearest[p.ff];
	 	 	 		dist[to.ff] = dist[p.ff] + 1;
	 	 	 	 	qu.push({to.ff, p.ff});
	 	 	 	}
	 	 	}
	 	}
	 	cerr << c << endl;
	}

	/*
	sort(bend(arrx));
	arrx.resize(unique(bend(arrx)) - arrx.begin());
	*/
	vector<pii> reqs;
	vector<vector<int>> order;
	for (int i = 0; i < q; ++i) {
	 	int a, b;
	 	scanf("%d%d", &a, &b);
	 	--a; --b;
	 	reqs.puba({a, b});
	 	/*
	 	queue<pii> qu;
	 	qu.push({a, -1});
	 	*/
	 	int nearest_el = nearest[a];
	 	/*
	 	while (szof(qu)) {
	 	 	pii p = qu.front();
	 	 	qu.pop();
	 	 	if (chosen[p.ff]) {
	 	 	 	nearest = p.ff;
	 	 	 	break;
	 	 	}
	 	 	for (pii to: graph[p.ff]) {
	 	 	 	if (to.ff != p.ss) {
	 	 	 	 	qu.push({to.ff, p.ff});
	 	 	 	}
	 	 	}
	 	}
	 	*/
		order.puba({tin[nearest_el], tin[b], i});
	}

	sort(bend(order));
	int posa = 0, posb = 0;
	vector<int> ans;
	ans.resize(q);

	for (int i = 0; i < q; ++i) {
	 	int a = reqs[order[i][2]].ff;
		int b = reqs[order[i][2]].ss;
		//int plca = get_lca(posa, posb);
		//int lca = get_lca(a, b);
		int lca_a = get_lca(a, posa);
		int pos = posa;
		while (pos != lca_a) {
		 	revert(pos);
		 	pos = binup[0][pos];
		}
		pos = a;
		while (pos != lca_a) {
		 	revert(pos);
		 	pos = binup[0][pos];
		}
		
		int lca_b = get_lca(b, posb);
		pos = posb;
		while (pos != lca_b) {
		 	revert(pos);
		 	pos = binup[0][pos];
		}
		pos = b;
		while (pos != lca_b) {
		 	revert(pos);
		 	pos = binup[0][pos];
		}
		posa = a;
		posb = b;
		//cout << get_ans() << "\n";
		ans[order[i][2]] = get_ans();
	}

	for (int val: ans) {
	 	cout << val << "\n";
	}

	cerr << clock() << endl;

	return 0;
}