#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#define ll long long
using namespace std;

int main() {
    freopen("urns-and-balls.in", "r", stdin);
    freopen("urns-and-balls.out", "w", stdout);

    int n, m;
    cin >> n >> m;
    vector<vector<int> > a(n);
    for (int i = 0; i < a.size(); i++) {
        a[i].push_back(i+1);
    }
    for (int ii = 0; ii < m; ii++) {
        int counti, from, to;
        cin >> counti >> from >> to;
        --from; --to;
        if (from == to) continue;
        if (from < to) {
            for (int i = from+counti-1; i >= from; i--) {
                a[to+i-from].insert(a[to+i-from].begin(), a[i].begin(), a[i].end());
                a[i].clear();
            }
        } else {
            for (int i = from; i < from+counti; i++) {
                a[to+i-from].insert(a[to+i-from].begin(), a[i].begin(), a[i].end());
                a[i].clear();
            }
        }
    }
    vector<int> ans(n);
    for (int i = 0; i < a.size(); i++) {
        for (int j = 0; j < a[i].size(); j++) {
            ans[a[i][j]-1] = i+1;
        }
    }
    for (int i = 0; i < ans.size(); i++) {
        cout << ans[i] << ' ';
    }
}