#include <bits/stdc++.h>
#define proj asdajslkdjalskd
using namespace std;

using proj = pair<string, int>;

int main() {
#if __APPLE__
    freopen("C.in", "r", stdin);
    freopen("C.out", "w", stdout);
#endif

    ios_base::sync_with_stdio(false);

    size_t n;
    while (cin >> n) {
        map<proj, vector<proj>> g;
        proj polycarp;
        for (size_t i = 0; i < n; ++i) {
            proj current;
            cin >> current.first >> current.second;
            if (i == 0) polycarp = current;

            size_t deps;
            cin >> deps;

            auto& cur_g = g[current];
            cur_g.resize(deps);

            for (size_t j = 0; j < deps; ++j) {
                cin >> cur_g[j].first >> cur_g[j].second;
            }
        }

        set<proj> alldeps;
        set<string> used = {polycarp.first};

        map<string, int> cur_lvl = {polycarp};
        while (!cur_lvl.empty()) {
            map<string, int> next_lvl;
            for (const auto& cur_proj : cur_lvl) {
                for (const auto& [name, version] : g[cur_proj]) {
                    if (used.find(name) == used.end()) {
                        next_lvl[name] = max(next_lvl[name], version);
                    }
                }
            }
            alldeps.insert(next_lvl.begin(), next_lvl.end());
            for (const auto& [name, version] : next_lvl) {
                used.insert(name);
            }
            cur_lvl.swap(next_lvl);
        }

        cout << alldeps.size() << '\n';
        for (const auto& [name, version] : alldeps) {
            cout << name << ' ' << version << '\n';
        }
    }
}
