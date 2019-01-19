#include <bits/stdc++.h>
#define FILENAME "01"
using namespace std;

void imp() {
    printf("IMPOSSIBLE");
}

void poss() {
    printf("POSSIBLE");
}

void solution() {
    int R, C, H, V;
    scanf("%d%d%d%d", &R, &C, &H, &V);
    
    int cnt = 0;
    vector<string> s(R);
    for (int i = 0; i < R; ++i) {
        cin >> s[i];
        for (int j = 0; j < C; ++j) {
            cnt += s[i][j] == '@';
        }
    }
    if (cnt % ((H + 1) * (V + 1)) != 0) {
        imp();
        return;
    }

    if (cnt == 0) {
        poss();
        return;
    }

    const int in_vert = cnt / (V + 1);
    vector<int> verts;
    for (int i = 0, now = 0; i < C; ++i) {
        for (int j = 0; j < R; ++j) {
            now += s[j][i] == '@';
        }
        if (now == in_vert) {
            verts.push_back(i);
            now = 0;
        } else if (now > in_vert) {
            imp();
            return;
        } else if (i == C - 1 && verts.size() != V + 1 && now != 0) {
            imp();
            return;
        }
    }
    if (verts.size() != V + 1) {
        imp();
        return;
    }

    const int in_hor = cnt / (H + 1);
    vector<int> hors;
    for (int i = 0, now = 0; i < R; ++i) {
        for (int j = 0; j < C; ++j) {
            now += s[i][j] == '@';
        }
        if (now == in_hor) {
            hors.push_back(i);
            now = 0;
        } else if (now > in_hor) {
            imp();
            return;
        } else if (i == R - 1 && hors.size() != H + 1 && now != 0) {
            imp();
            return;
        }
    }
    if (hors.size() != H + 1) {
        imp();
        return;
    }

    verts.push_back(-1);
    hors.push_back(-1);
    sort(verts.begin(), verts.end()); sort(hors.begin(), hors.end());
    int in_each = cnt / (H + 1) / (V + 1);
    for (int i = 0; i + 1 < hors.size(); ++i) {
        for (int j = 0; j + 1 < verts.size(); ++j) {
            int here = 0;
            for (int i1 = hors[i] + 1; i1 <= hors[i + 1]; ++i1) {
                for (int j1 = verts[j] + 1; j1 <= verts[j + 1]; ++j1) {
                    here += s[i1][j1] == '@';
                }
            }
            if (here != in_each) {
                imp();
                return;
            }
        }
    }
    poss();
}

void run_solution();

int main() {
    run_solution();
}

void run_solution() {
    int T;
    scanf("%d", &T);

    for (int test = 1; test <= T; ++test) {
        printf("Case #%d: ", test);
        solution();
        putchar('\n');
    }
}
