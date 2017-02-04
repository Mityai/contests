 #include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <cmath>
#include <string>
#include <set>

typedef long long ll;

using namespace std;

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n;
    cin >> n;

    vector<vector<int> > d(n, vector<int> (n));

    for (int i = 0; i < n; i++) {
        d[i][i] = 1;
    }

    string s;
    cin >> s;

    vector<set<int> > p(n);
    for (int i = 0; i < n; i++) {
        p[i] = i;
    }

    for (int k = 1; k < n; k++) {
        for (int i = 0; i < n - k; i++) {
            int j = i + k;

            if (d[i][i] + d[i + 1][j] < d[i][j - 1] + d[j][j]) {
                d[i][j] = d[i][i] + d[i + 1][j];
            } else {
                d[i][j] = d[i][j - 1] + d[j][j];
            }

            if (s[i] == s[j]) {
                if (d[i][j] > d[i + 1][j]) {
                    d[i][j] = d[i + 1][j];
                    p[i].insert(j);
                }
            }

            if (s[i] == s[i + 1]) {
                if (d[i][j] > d[i + 1][j]) {
                    d[i][j] = d[i + 1][j];
                    p[i].insert(i + 1);
                }
            }

            if (s[j] == s[j - 1]) {
                if (d[i][j] > d[i][j - 1]) {
                    d[i][j] = d[i][j - 1];
                    p[j - 1].insert(j);
                }
            }

            for (int z = i; z <= j; z++) {
                cout << s[z];
            }
            cout << " = " << d[i][j] << endl;
        }
    }

    cout << d[0][n - 1] << endl;

    vector<char> used(n, false);
    for (int i = 0; i < n; i++) {
        if (!used[p[i]]) {
            cout << i + 1 << ' ' << p[i] + 1 << ' ' << s[i] << endl;
            used[p[i]] = true;
        }
    }
}