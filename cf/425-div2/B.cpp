// GLEB --- PIDOR
#include <bits/stdc++.h>
using namespace std;

#if __APPLE__
#define eprintf(...) fprintf(stderr, __VA_ARGS__)
#else
#define eprintf(...)
#endif

const int N = 1e5;
const int A = 26;

int main() {
    ios_base::sync_with_stdio(false);
    string alpha;
    cin >> alpha;

    vector<char> good(A);
    for (char c : alpha) {
        good[c - 'a'] = true;
    }

    string s;
    cin >> s;
    int m = s.length();

    string a, b;
    bool ast = false;
    for (char c : s) {
        if (c == '*') ast = true;
        else if (!ast) a += c;
        else b += c;
    }

    int n;
    cin >> n;

    for (int f = 0; f < n; ++f) {
        string t;
        cin >> t;

        bool ok = true;
        if (a.size() + b.size() > t.size()) ok = false;
        if (ok) {
            string ta = t.substr(0, a.size());
            string tb = t.substr(t.size() - b.size());
            for (int i = 0; i < ta.size(); ++i) {
                if (a[i] == '?' && !good[ta[i] - 'a']) {
                    ok = false;
                    break;
                } else if (a[i] != '?') {
                    if (a[i] != ta[i]) {
                        ok = false;
                        break;
                    }
                }
            }
            for (int i = 0; i < tb.size(); ++i) {
                if (b[i] == '?' && !good[tb[i] - 'a']) {
                    ok = false;
                    break;
                } else if (b[i] != '?') {
                    if (b[i] != tb[i]) {
                        ok = false;
                        break;
                    }
                }
            }
            if (ast) {
                for (int i = ta.size(); i < t.size() - tb.size(); ++i) {
                    if (good[t[i] - 'a']) {
                        ok = false;
                        break;
                    }
                }
            } else {
                if (a.size() + b.size() != t.size()) ok = false;
            }
        }
        if (ok) {
            puts("YES");
        } else {
            puts("NO");
        }
    }
}
