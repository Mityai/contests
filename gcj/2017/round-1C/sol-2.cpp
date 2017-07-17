#include <iostream>
#include <algorithm>
#include <set>
#include <vector>
#include <string>
#include <cmath>
#include <map>
#include <cstdio>
#include <cassert>

#define X first
#define Y second

using namespace std;

typedef long long ll;
typedef long double ld;

const long double inf = 1e18 + 7;
const long double eps = 1e-18;


struct st {
    int l, r;
    int id;
    st(int l, int r, int id): l(l), r(r), id(id) {}

    bool operator < (const st &b) {
        return l < b.l;
    }
};

void prtans(int ans, int tt) {
    cout << "Case #" << tt + 1 << ": " << ans << endl; 
} 

int main() {
ios_base::sync_with_stdio(0);
    freopen("B.in", "r", stdin);
    freopen("B.out", "w", stdout);

    int t;
    cin >> t;
    for (int tt = 0; tt < t; ++tt) {
        int n, m;
        cin >> n >> m;
        vector<pair<int, int> > a, b;


        int suma = 0;
        int sumb = 0;
        for (int i = 0; i < n; ++i) {
            int l, r;
            cin >> l >> r;
            a.push_back({l, r});
            suma += r - l;
        }
        sort(a.begin(), a.end());


        for (int i = 0; i < m; ++i) {
            int l, r;
            cin >> l >> r;
            b.push_back({l, r});
            sumb += r - l;
        }
        sort(b.begin(), b.end());
        
        vector<st> dt;
        for (auto x : a)
            dt.push_back(st(x.first, x.second, 0));
        for (auto x : b)
            dt.push_back(st(x.first, x.second, 1));

        sort(dt.begin(), dt.end());

        vector<vector<pair<int, int> > > intervals(2, vector<pair<int, int> > ());

        if (dt.size() > 1)
            for (int i = 0; i < dt.size(); ++i) {
                if (dt[i].id == dt[(i + 1) % dt.size()].id) {
                    int len = dt[(i + 1) % dt.size()].l - dt[i].r;
                    if (len < 0)
                        len = dt[(i + 1) % dt.size()].l + 24 * 60 - dt[i].r;
                    intervals[dt[i].id].push_back({len, i});
                }
            }
        
        sort(intervals[0].begin(), intervals[0].end());
        sort(intervals[1].begin(), intervals[1].end());

        vector<bool> okfl(dt.size());

        for (int i = 0; i < intervals[0].size(); ++i) {
            if (suma + intervals[0][i].first <= 720)
                okfl[intervals[0][i].second] = 1, suma += intervals[0][i].first;
        }

        for (int i = 0; i < intervals[1].size(); ++i) {
            if (sumb + intervals[1][i].first <= 720)
                okfl[intervals[1][i].second] = 1, sumb += intervals[1][i].first;
        }

        int ans = 0;
        for (int i = 0; i < dt.size(); ++i) {
            if (dt[i].id != dt[(i + 1) % dt.size()].id){
                ++ans;
                continue;
            }
            if (!okfl[i])
                ans += 2;
        }
        prtans(ans, tt);
    }
    return 0;
}
