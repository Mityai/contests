#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string>
using namespace std;

int res[21][31];    

int main() {
    freopen("stroll.in", "r", stdin);
    freopen("stroll.out", "w", stdout);
    
    int n, m;
    int start_i = -1, start_j, end_i, end_j;
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            char c;
            cin >> c;
            if (c == 'R') {
                res[i][j] = -1;
            } else if (c == 'B' && start_i == -1) {
                start_i = i;
                start_j = j;
            } else if (c == 'B') {
                end_i = i;
                end_j = j;
            }
        }
    }
    res[start_i][start_j] = 1;
    for (int i = start_i; i <= end_i; i++) {
        for (int j = start_j; j <= end_j; j++) {
            if ((i != start_i || j != start_j) && res[i][j] != -1) {
                res[i][j] = 0;
                if (j-1 >= start_j && res[i][j-1] != -1) {
                    res[i][j] += res[i][j-1];
                }
                if (i-1 >= start_i && res[i-1][j] != -1) {
                    res[i][j] += res[i-1][j];
                }
            }
        }
    }
    cout << res[end_i][end_j];

    return 0;
}