#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <set>
using namespace std;
 
int main() {
    freopen("crowded.in", "r", stdin);
    freopen("crowded.out", "w", stdout);
     //crowded.in
    int n, d;
    cin >> n >> d;
    vector<pair<int, int> > a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i].first >> a[i].second;
    }
    sort(a.begin(), a.end());
 
    multiset<int> Left, Right;
    int ans = 0;
    int l = 0, r = 0;
    for (int i = 0; i < n; i++) {
        while (r < n && a[i].first + d >= a[r].first) {
            Right.insert(a[r].second);
            r++;
        }
        while (a[l].first + d < a[i].first) {
            Left.erase(Left.find(a[l].second));
            l++;
        }
        int check = 0;
        if (!Left.empty()) {
            int maxLeft = *--Left.end();
            if (maxLeft >= 2*a[i].second) {
                check++;
            }
        }
        if (!Right.empty()) {
            int maxRight = *--Right.end();
            if (maxRight >= 2*a[i].second && maxRight >= 2*a[i].second) {
                check++;
            }
        }
        if (check == 2) ans++;
        Left.insert(a[i].second);
        Right.erase(Right.find(a[i].second));
    }
    cout << ans;
 
    return 0;
}