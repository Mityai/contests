#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <iterator>
#include <string>
#include <vector>
#include <set>
#include <map>
using namespace std;

#define ll long long

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n, k;
    cin >> n >> k;
    string s;
    getline(cin, s);
    getline(cin, s);
    
    int t = 1;
    for (int i = 19; i < s.length()-5; i++) {
        if (s[i] == ' ') {
            t++;
        }
    }
    vector<set<string> > adv(t);
    vector<vector<string> > wasnt(n);
    for (int i = 0; i < n; i++) {
        string temp;
        int sch = 0;
        for (int j = 19; j < s.length()-5; j++) {
            if (s[j] == ' ') {
                adv[sch].insert(temp);
                wasnt[i].push_back(temp);
                temp = "";
                sch++;
            } else {
                temp += s[j];
            }
        }
        adv[sch].insert(temp);
        wasnt[i].push_back(temp);
        getline(cin, s);
    }
    ll kol = 1;
    vector<map<string, int> > b(t);
    for (int i = 0; i < t; i++) {
        int k = 0;
        for (set<string>::iterator it = adv[i].begin(); it != adv[i].end(); it++) {
            b[i][*it] = k;
            k++;
        }
        kol *= adv[i].size();
    }
    vector<int> kans(t);
    int del = kol;
    int sum = 0;
    for (int i = 0; i < t; i++) {
        bool next = false;
        for (int j = 0; j <= adv[i].size(); j++) {
            if (sum+j*(del/adv[i].size()) >= k && next == false) {
                kans[i] = j-1;
                sum += (j-1)*(del/adv[i].size());
                del = (del/adv[i].size());
                next = true;
            }
        }
    }
    int sdv = 0;
    for (int i = 0; i < n; i++) {
        int counter = 0;
        for (int j = 0; j < wasnt[i].size(); j++) {
            if (kans[j] > b[j][wasnt[i][j]]) {
                sdv++;
                continue;
            } else if (kans[j] == b[j][wasnt[i][j]]) {
                counter++;
            }
        }
        if (counter == wasnt[i].size()) {
            sdv++;
        }
    }
    k += sdv;
    del = kol;
    sum = 0;
    for (int i = 0; i < t; i++) {
        bool next = false;
        for (int j = 0; j <= adv[i].size(); j++) {
            if (sum+j*(del/adv[i].size()) >= k && next == false) {
                kans[i] = j-1;
                sum += (j-1)*(del/adv[i].size());
                del = (del/adv[i].size());
                next = true;
            }
        }
    }
    for (int i = 0; i < kans.size(); i++) {
        int j = 0;
        for (set<string>::iterator it = adv[i].begin(); it != adv[i].end(); it++) {
            if (j == kans[i]) {
                cout << *it << " ";
            }
            j++;
        }
    }

    return 0;
}