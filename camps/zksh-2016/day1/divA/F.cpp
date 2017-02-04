#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

int main() {
    int n;
    scanf("%d", &n);

    set<string> friends;
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        friends.insert(s);
    }

    int m;
    scanf("%d", &m);

    set<string> also;
    for (int i = 0; i < m; i++) {
        string s;
        cin >> s;
        also.insert(s);
    }

    vector<string> A, B, C;
    for (string s : friends) {
        if (also.count(s)) {
            B.push_back(s);
        }
        A.push_back(s);
    }

    for (string s : also) {
        if (!friends.count(s)) {
            C.push_back(s);
        }
    }

    sort(A.begin(), A.end());
    sort(B.begin(), B.end());
    sort(C.begin(), C.end());

    cout << "Friends: ";
    for (int i = 0; i < (int)A.size(); i++) {
        cout << A[i];
        if (i + 1 < (int)A.size()) {
            cout << ", ";
        }
    }
    cout << endl;

    cout << "Mutual Friends: ";
    for (int i = 0; i < (int)B.size(); i++) {
        cout << B[i];
        if (i + 1 < (int)B.size()) {
            cout << ", ";
        }
    }
    cout << endl;

    cout << "Also Friend of: ";
    for (int i = 0; i < (int)C.size(); i++) {
        cout << C[i];
        if (i + 1 < (int)C.size()) {
            cout << ", ";
        }
    }
    cout << endl;
}
