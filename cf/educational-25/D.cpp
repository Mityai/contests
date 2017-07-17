#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int LEN = 1e6 + 123;

int main() {
    string s, t;
    cin >> s >> t;

    vector<ll> cnts(26);
    int ask = 0;
    for (char c : s) {
        if (c == '?') ++ask;
        else ++cnts[c - 'a'];
    }

    vector<ll> cntt(26);
    for (char c : t) {
        ++cntt[c - 'a'];
    }

    ll lb = 0, rb = s.size() + 1;
    while (lb + 1 < rb) {
        ll mb = (lb + rb) / 2;
        ll need = 0;
        for (int i = 0; i < 26; ++i) {
            need += max(0ll, cntt[i] * mb - cnts[i]);
        }
        if (need <= ask) lb = mb;
        else rb = mb;
    }

    vector<ll> can(26);
    for (int i = 0; i < 26; ++i) {
        can[i] = max(0ll, cntt[i] * lb - cnts[i]);
    }

    int i = 0;
    for (char& c : s) {
        if (c == '?') {
            while (i < 26 && can[i] == 0) {
                ++i;
            }
            if (i == 26) {
                c = 'a';
            } else {
                c = 'a' + i;
                --can[i];
            }
        }
    }

    cout << s << endl;
}
