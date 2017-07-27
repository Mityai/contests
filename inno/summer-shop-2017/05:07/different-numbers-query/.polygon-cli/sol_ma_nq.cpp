#include <cstdio>
#include <vector>
#include <tuple>
using namespace std;

const int LGN = 17;
const int N = 100500;
int up[LGN][N];

vector<pair<int, int>> E[N];

int V[N];
int D[N];

void DFS(int x, int p = 0) {
	up[0][x] = p;
	D[x] = D[p] + 1;
	for (int d = 1; d < LGN; d++)
		up[d][x] = up[d - 1][up[d - 1][x]];
	for (int i = 0; i < E[x].size(); i++) {
		int y, w;
		tie(y, w) = E[x][i];
		if (y == p) {
			E[x].erase(E[x].begin() + i);
			--i;
			continue;
		}
		DFS(y, x);
		V[y] = w;
	}
}

int lca(int x, int y) {
	if (D[x] > D[y])
		swap(x, y);
	for (int d = LGN - 1; d >= 0; d--) {
		if (D[y] - (1 << d) >= D[x])
			y = up[d][y];
	}
	if (x == y)
		return x;
	for (int d = LGN - 1; d >= 0; d--) {
		if (up[d][x] != up[d][y])
			x = up[d][x], y = up[d][y];
	}
	return up[0][x];
}

int used[N];

int main() {
	int n, q;
	scanf("%d %d", &n, &q);
	for (int i = 0; i < n - 1; i++) {
		int a, b, w;
		scanf("%d %d %d", &a, &b, &w);
		w = min(w, N - 1);
		--a, --b;
		E[a].emplace_back(b, w);
		E[b].emplace_back(a, w);
	}
	DFS(0);
	for (int i = 1; i <= q; i++) {
		int a, b;
		scanf("%d %d", &a, &b);
		--a, --b;
		int l = lca(a, b);
		while (a != l) {
			used[V[a]] = i;
			a = up[0][a];
		}
		while (b != l) {
			used[V[b]] = i;
			b = up[0][b];
		}
		int ans = 0;
		while (used[ans] == i)
			ans++;
		printf("%d\n", ans);
	}
}
