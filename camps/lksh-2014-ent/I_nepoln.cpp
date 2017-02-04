#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <string>
#include <climits>
#include <map>
#define WITHFILES 1
#define PROBLEM "xx"
#define ll long long
using namespace std;

int n, k, m;
int ans = INT_MAX;
bool a[1000][1000];
int t[1000][1000];
bool ver[1000][1000];
bool hor[1000][1000];
bool diag[1000][1000];

void rec_ver(int i, int j, int step) {

}

void rec_hor(int i, int j, int step) {

}

void rec_diag(int i, int j, int step) {

}

int main() {
    #if __APPLE__
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #else
        freopen(PROBLEM ".in", "r", stdin);
        freopen(PROBLEM ".out", "w", stdout);
    #endif

    cin >> n >> k >> m;
    for (int i = 0; i < m; i++) {
        int ii, jj;
        cin >> ii >> jj;
        a[--ii][--jj] = 1;
        t[ii][jj] = i + 1;
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (!ver[i][j]) {
                rec_ver(i, j, 1);
            }
            if (!hor[i][j]) {
                rec_hor(i, j, 1);
            }
            if (!diag[i][j]) {
                rec_diag(i, j, 1);
            }
        }
    }
    cout << (ans == INT_MAX ? 0 : ans);
}