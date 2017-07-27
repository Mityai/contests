#include <iostream>
#include <algorithm>
#include <vector>
#include <unordered_map>
#include <map>
#include <algorithm>
#include <string>
#include <cmath>
#include <math.h>

using namespace std;

#define pr make_pair

vector<vector<pair<int, int> > > grph;
int steps[100000][20];
int tin[100000];
int tout[100000];
vector<int> glub;
vector<int> sum;
int timer = 0;

void dfs(int v, int p = 0, int depth = 0, int sm = 0) {
	tin[v] = timer++;
	glub[v] = depth;
	sum[v] = sm;
	steps[v][0] = p;
	for (int i = 1; i < 20; ++i) {
		steps[v][i] = steps[steps[v][i - 1]][i - 1];
	}
	for (auto u : grph[v]) {
		if (u.first != p) {
			dfs(u.first, v, depth + 1, sm + u.second);
		}
	}
	tout[v] = timer++;
}

bool is_par(int v1, int v2) {
	return (tin[v1] < tin[v2] && tout[v1] > tout[v2]);
}

int lca(int v1, int v2) {
	if (is_par(v1, v2)) {
		return v1;
	}
	if (is_par(v2, v1)) {
		return v2;
	}
	for (int i = 19; i > -1; --i) {
		if (!is_par(steps[v1][i], v2)) {
			v1 = steps[v1][i];
		}
	}
	return steps[v1][0];
}

int main() {
	int n;
	cin >> n;
	int a, b;
	glub.resize(n);
	sum.resize(n);
	grph.resize(n);
	for (int i = 0; i < n - 1; i++){
		cin >> a >> b;
		grph[a - 1].push_back(pr(b - 1, 1));
		grph[b - 1].push_back(pr(a - 1, 0));
	}
	dfs(0);
	int m;
	cin >> m;
	int pred;
	for (int i = 0; i < m; i++){
		cin >> a >> b;
		a--;
		b--;
		pred = lca(a, b);
		swap(a, b);
		if (sum[a] - sum[pred] == glub[a] - glub[pred] && sum[b] - sum[pred] == 0){
			cout << "Yes" << endl;
			continue;
		}
		if (a == b){
			cout << "Yes" << endl;
			continue;
		}
		cout << "No" << endl;
	}
	#ifdef _MSC_VER
	system("pause");
	#endif
}
