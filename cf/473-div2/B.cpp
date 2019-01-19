#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
#if __APPLE__
    freopen("B.in", "r", stdin);
    freopen("B.out", "w", stdout);
#endif

    ios_base::sync_with_stdio(false);

    int n, k, m;
    cin >> n >> k >> m;

    vector<string> words(n);
    map<string, int> id;
    for (int i = 0; i < n; ++i) {
        cin >> words[i];
        id[words[i]] = i;
    }

    vector<int> cost(n);
    for (int i = 0; i < n; ++i) {
        cin >> cost[i];
    }

    for (int i = 0; i < k; ++i) {
        int num;
        cin >> num;
        vector<int> sim(num);
        int min_value = 1e9;
        for (int& val : sim) {
            cin >> val;
            --val;
            min_value = min(min_value, cost[val]);
        }
        for (int val : sim) {
            cost[val] = min_value;
        }
    }

    ll ans = 0;
    for (int i = 0; i < m; ++i) {
        string word;
        cin >> word;
        ans += cost[id[word]];
    }

    cout << ans << endl;
}
