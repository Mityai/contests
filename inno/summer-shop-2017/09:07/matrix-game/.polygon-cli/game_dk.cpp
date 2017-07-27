#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <string>
using namespace std;
int n, m;
bool in_field(int x, int y) {
		return ((x >= 0) && (y >= 0) && (x < n) && (y < m));
	}
int p[1031][1031];
int a[1031][1031];
int dfs(int i, int j) {
		if (p[i][j] == 0) {
			return 0;
		}
		if (p[i][j] == 1) {
			return 1;
		}
		if (p[i][j] == 2) {
			return -1;
		}
		int x1 = -2;
		int x2 = -2;
		p[i][j] = 2;
		if (in_field(i + a[i][j], j) == true) {
			x1 = dfs(i + a[i][j], j);
		}
		if (in_field(i, j + a[i][j]) == true) {
			x2 = dfs(i, j + a[i][j]);                              
		}
		if (x1 < 0 && x2 < 0) {
			return -1;
		}
		if (x1 == 0 || x2 == 0) {
			p[i][j] = 1;
			return 1;
		}
		p[i][j] = 0;
		return 0;
	}


int main() {
	freopen("game.in", "r", stdin);
	freopen("game.out", "w", stdout);

	scanf("%d %d", &n, &m);
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m-1; j++) {
				scanf("%d ", &a[i][j]);
			}
			scanf("%d\n", &a[i][m-1]);
		}
		int si, sj;
		scanf("%d %d", &si, &sj);
		si--;
		sj--;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				p[i][j] = -1;
			}
		}

		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				p[i][j] = -1;
			}
		}
		
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				if ((in_field(i + a[i][j], j)
						|| in_field(i, j + a[i][j])) == false) {
					p[i][j] = 0;
				};
			}
		}
		int ress = dfs(si, sj);
		if (ress == 1) cout << "Anton";
		if (ress == 0) cout << "Yasha";
		if (ress == -1) cout << "draw";
}