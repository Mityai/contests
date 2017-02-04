#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

vector<int> SuffixArray(const string &s) {
    int n = (int)s.size();
    int alpha = 0;
    for (char c : s) {
        alpha = max(alpha, (int)c + 1);
    }
    
    vector<int> count(alpha);
    vector<int> h(max(n, alpha));
    vector<int> eq(n);
    
    for (int i = 0; i < n; i++) {
        count[eq[i] = int(s[i])]++;
    }
    for (int i = 1; i < alpha; i++) {
        h[i] = h[i - 1] + count[i - 1];
    }
    
    vector<int> p(n);
    {
        vector<int> nh = h;
        for (int i = 0; i < n; i++) {
            p[nh[eq[i]]++] = i;
        }
    }
    
    vector<int> np(n);
    vector<int> neq(n);
    for (int k = 1; k < n; k <<= 1) {
        for (int i = 0; i < n; i++) {
            int j = (p[i] - k + n) % n;
            np[h[eq[j]]++] = j;
        }
        int nc = 0;
        h[nc++] = 0;
        neq[np[0]] = nc - 1;
        for (int i = 1; i < n; i++) {
            if (eq[np[i]] != eq[np[i - 1]] || eq[(np[i] + k) % n] != eq[(np[i - 1] + k) % n]) {
                h[nc++] = i;
            }
            neq[np[i]] = nc - 1;
        }
        p.swap(np);
        eq.swap(neq);
    }
    return p;
}

vector<int> getLCP(const vector<int> &sa, const string &s) {
    int k = 0;
    int n = (int)sa.size();
    vector<int> rev(n);
    for (int i = 0; i < n; i++) {
        rev[sa[i]] = i;
    }
    vector<int> lcp(n);
    for (int i = 0; i < n; i++) {
        k = max(k - 1, 0);
        int j = rev[i] + 1;
        if (j >= n) continue;
        j = sa[j];
        while (i + k < n && j + k < n && s[i + k] == s[j + k]) {
            ++k;
        }
        lcp[rev[i]] = k;
    }
    return lcp;
}

int main() {
#if __APPLE__
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#else
    freopen("kthsubstr.in", "r", stdin);
    freopen("kthsubstr.out", "w", stdout);
#endif
    
    string s;
    cin >> s;
    s += "$";
    
    ll n;
    cin >> n;
    
    auto sa = SuffixArray(s);
    auto lcp = getLCP(sa, s);
    s.pop_back();
    
    ll sum = 0;
    for (int i = 1; i < (int)sa.size(); i++) {
        ll len = (ll)s.size() - sa[i];
        sum += len - lcp[i - 1];
        if (n <= sum) {
            cout << s.substr(sa[i], ((ll)s.size() - (sum - n)) - (ll)sa[i]) << endl;
            return 0;
        }
        //cout << lcp[i] << ' ' << s.substr(sa[i]) << endl;
    }
    
    cout << s.substr(sa[(int)sa.size() - 1]) << endl;
}
