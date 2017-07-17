#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

typedef long long ll;

int main() {
#if __APPLE__
    freopen("B.in", "r", stdin);
    freopen("B.out", "w", stdout);
#endif

    ios_base::sync_with_stdio(false);

    int c;
    cin >> c;

    map<string, vector<pair<string, string>>> q;
    for (int i = 0; i < c; ++i) {
        string city;
        int n;
        cin >> city >> n;

        for (int j = 0; j < n; ++j) {
            string t;
            string name;
            cin >> t >> name;
            q[city].push_back({t, name});
        }
    }

    int m;
    cin >> m;

    for (int i = 0; i < m; ++i) {
        int l;
        cin >> l;

        vector<string> cities(l);
        for (int j = 0; j < l; ++j) {
            cin >> cities[j];
        }

        for (int h = 0; h < 24; ++h) {
            bool ok = true;
            vector<string> ans;
            for (string& city : cities) {
                string here;
                for (auto& v : q[city]) {
                    if (v.first[h] == '.') {
                        here = v.second;
                        break;
                    }
                }
                if (here.empty()) {
                    ok = false;
                    break;
                }
                ans.push_back(here);
            }

            if (ok) {
                cout << "Yes ";
                for (string& s : ans) {
                    cout << s << ' ';
                }
                cout << '\n';
                break;
            } else if (h == 23) {
                cout << "No\n";
            }
        }
    }
}
