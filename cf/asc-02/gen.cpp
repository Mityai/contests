#include <bits/stdc++.h>
using namespace std;

int main() {
    freopen("dfa.in", "w", stdout);
    
    string s(26, 'a');
    const int ALPHA = 26;
    cout << s << endl;
    const int K = 1000;
    const int S = 1;
    const int L = 1;
    const int E = K;
    cout << K << ' ' << S << ' ' << L << ' ' << E << endl;
    for (int i = 0; i < K; ++i) {
        int to = i + 2;
        if (to > K) to = 1;
        for (int j = 0; j < ALPHA; ++j) {
            cout << to << ' ';
        }
        cout << endl;
    }
    for (int i = 0; i < K; ++i) {
        for (int j = 0; j < ALPHA; ++j) {
            cout << 0 << ' ';
        }
        cout << endl;
    }
    cout << K - 1 << endl;
}
