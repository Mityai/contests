#include <bits/stdc++.h>
using namespace std;

string s;
int ind[26];
int sec;

char res[2][13];

int main() {
    cin >> s;
    for (int i = 0; i < s.size(); i++) {
        if (ind[s[i] - 'A']) {
            sec = i;
        } else {
            ind[s[i] - 'A'] = i + 1;
        }
    }
    for (int i = 0; i < 26; i++) {
        ind[i]--;
    }

    if (sec == ind[s[sec]-'A']+1) {
        cout << "IM" << endl;
        return 0;
    }

    int d = sec - ind[s[sec]-'A'];
    int l = d / 2;
    d -= l;

    int inde = 13- l, i;
    for (i = ind[s[sec]-'A'] + 1; inde < 13; i++, inde++) {
        res[0][inde] = s[i];
    }
    for (i, inde = 12; inde >= 0 && i < s.size(); i++, inde--) {
        res[1][inde] = s[i];
    }

    if (i == s.size()) {
        for (i = 0; inde >= 0; i++, inde--) {
            res[1][inde] = s[i];
        }
        for (i, inde = 0; inde < 13 && i < ind[s[sec]-'A']; i++, inde++) {
            res[0][inde] = s[i];
        }
    } else {
        for (i, inde = 0; inde < 13 && i < s.size(); i++, inde++) {
            res[0][inde] = s[i];
        } 
        for (i = 0; i < ind[s[sec]-'A']; i++, inde++) {
            res[0][inde] = s[i];
        }
    }

    for (int j = 0; j < 2; j++) {
        for (i = 0; i < 13; i++) {
            cout << res[j][i];
        }
        cout << endl;
    }
}
