#include <bits/stdc++.h>
using namespace std;

const int N = 500;

int cnt;
bool used[N];
vector<int> g[N];

void dfs(int v) {
    ++cnt;
    used[v] = true;
    for (int u : g[v]) {
        if (!used[u]) {
            dfs(u);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);

    int n;
    cin >> n;

    for (int i = 0; i < n; ++i) {
        string s;
        cin >> s;

        for (int j = 0; j < n; ++j) {
            if (s[j] == '?' || s[j] == 'W') {
                g[i].push_back(j);
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        memset(used, 0, sizeof used);
        cnt = 0;
        dfs(i);
        if (cnt == n) {
            cout << i + 1 << endl;
        }
    }
}
