#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

const int L = 101;

pair<vector<int>, vector<int>> suffixArray(const vector<int>& s) {
    int n = s.size();
    vector<int> sa(n);
    vector<int> classes(n);
    vector<int> tmp(n);
    vector<int> buck(max(L, n));

    for (int i = 0; i < n; i++) {
        buck[s[i]]++;
    }

    int sum = 0;
    for (int i = 0; i < L; i++) {
        int t = buck[i];
        sum += t;
        buck[i] = sum - t;
    }

    for (int i = 0; i < n; i++) {
        sa[buck[s[i]]++] = i;
    }

    classes[sa[0]] = 0;
    for (int i = 1; i < n; i++) {
        classes[sa[i]] = classes[sa[i - 1]] + (s[sa[i]] != s[sa[i - 1]]);
    }

    int cn = classes[sa[n - 1]] + 1;
    for (int l = 1; l < n; l <<= 1) {
        for (int i = 0; i < n; i++) {
            buck[i] = 0;
        }
        for (int i = 0; i < n; i++) {
            buck[classes[i]]++;
        }
        sum = 0;
        for (int i = 0; i < cn; i++) {
            int t = buck[i];
            sum += t;
            buck[i] = sum - t;
        }

        for (int i = 0; i < n; i++) {
            tmp[buck[classes[(sa[i] - l + n) % n]]++] = (sa[i] - l + n) % n;
        }

        sa = tmp;
        tmp[sa[0]] = 0;
        for (int i = 1; i < n; i++) {
            tmp[sa[i]] = tmp[sa[i - 1]] +
                (classes[sa[i]] != classes[sa[i - 1]]
                 || classes[(sa[i] + l) % n] != classes[(sa[i - 1] + l) % n]);
        }
        cn = tmp[sa[n - 1]] + 1;
        classes = tmp;
    }

    return {sa, classes};
}

int main() {
    int n;
    while (scanf("%d", &n) == 1) {
        if (n == 0) return 0;
        vector<int> s(n);
        for (int i = 0; i < n; ++i) {
            scanf("%d", &s[i]);
        }
        auto sa = suffixArray(s);
        for (int x : sa.se) {
            printf("%d ", x);
        }
        puts("");
        int l = 0, r = 0;
        while (l < n) {
            while (r < n && sa.se[sa.fi[r]] == sa.se[sa.fi[l]]) {
                ++r;
            }
            sort(sa.fi.begin() + l, sa.fi.begin() + r);
            l = r;
        }
        for (int x : sa.fi) {
            printf("%d ", x + 1);
        }
        puts("");
    }
}
