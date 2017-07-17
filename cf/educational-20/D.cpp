#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);

    int k;
    cin >> k;

    string s;
    getline(cin, s);
    getline(cin, s);

    int n = s.length();

    vector<int> a;
    a.push_back(-1);
    for (int i = 0; i < n; ++i) {
        if (s[i] == ' ' || s[i] == '-') {
            a.push_back(i);
        }
    }
    a.push_back(n - 1);

    int m = a.size();
    int lb = 0, rb = n + 1;
    while (lb + 1 < rb) {
        int mb = (lb + rb) / 2;
        int cnt = 0;
        for (int i = 0; i + 1 < m;) {
            int j = i;
            while (j + 1 < m && a[j + 1] - a[i] <= mb) {
                ++j;
            }
            if (j > i && a[j] - a[i] <= mb) {
                ++cnt;
                i = j;
            } else {
                cnt = 1e9;
                break;
            }
        }
        if (cnt <= k) {
            rb = mb;
        } else {
            lb = mb;
        }
    }

    printf("%d\n", rb);
}
