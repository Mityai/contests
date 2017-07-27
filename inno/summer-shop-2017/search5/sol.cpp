#include <bits/stdc++.h>
 
using namespace std;
const int N = 1e6 + 10;
const int A = 26;
int b = 0;
int q[N];
 
int e = 0;
struct aho_corasik {
    int total, go[N][A], link[N], next_term[N], len[N], mod[N];
    vector<int> term[N];
    vector<int> gde;
    aho_corasik(): total(1) {
        gde.resize(N);
        memset(mod, 0, sizeof(mod));
        memset(go, 0, sizeof(go));
        memset(link, -1, sizeof(link));
        memset(next_term, -1, sizeof(next_term));
        memset(len, 0, sizeof(len));
    }
    void add(string s, int num) {
        int j = 0;
        for (int i = 0; i < s.size(); ++i) {
            int c = s[i] - 'a';
            if (go[j][c] == 0) go[j][c] = total++;
            j = go[j][c];
        }
        term[j].push_back(num);
        gde[num] = j;
    }
    void build() {
 
        q[e++] = 0;
        while (b < e) {
            int v = q[b++];
            next_term[v] = (!term[v].empty()) ? v : ((link[v] == -1) ? 0 : next_term[link[v]]);
            for (int c = 0; c < A; ++c)
                if (go[v][c] == 0)
                    go[v][c] = (link[v] == -1) ? 0 : go[link[v]][c];
                else {
                    link[go[v][c]] = (link[v] == -1) ? 0 : go[link[v]][c];
                    len[go[v][c]] = len[v] + 1;
                    q[e++] = v;
                }
        }
    }
    void find_occur(string s, int n) {
        vector<vector<int>> ans(n);
        for (int i = 0, j = 0; i < s.size(); ++i) {
            int c = s[i] - 'a';
            j = go[j][c];
            mod[j]++;
        }
        for (int i = e; i >= b; --i) {
            mod[next_term[q[i]]] += mod[q[i]];
        }
        for (int i = 0; i < n; ++i) {
            cout << mod[gde[i]] << endl;
        }
    }
};
 
 
void get_ans_for_aho() {
    string s;
    int n;
    cin >> n;
    aho_corasik *A = new aho_corasik();
    for (int i(0); i < n; ++i) {
        string t;
        cin >> t;
        A->add(t, i);
    }
    cin >> s;
    A->build();
    A->find_occur(s, n);
}
 
int main() {
    freopen("search5.in", "r", stdin);
    freopen("search5.out", "w", stdout);
 
    get_ans_for_aho();
    return 0;
}
