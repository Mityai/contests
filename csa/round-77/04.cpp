#include <bits/stdc++.h>
#define end asdasdjaklsj
using namespace std;

const int N = 1e6;

vector<map<char, int>> to(N);
vector<int> end(N);
vector<int> sub(N);

const int root = 0;
int tc = 0;

void add(const char* s) {
    int node = root;
    for (int i = 0; s[i] != '\0'; ++i) {
        if (to[node].count(s[i]) == 0) {
            to[node][s[i]] = ++tc;
        }
        node = to[node][s[i]];
    }
    ++end[node];
}

double ans = 0.0;
double all;

void dfs(int node, int d = 0) {
    for (const auto& it : to[node]) {
        dfs(it.second, d + 1);
        double there = sub[it.second] + end[it.second];
        sub[node] += there;
    }

    double cur = end[node] * 1.0 * (end[node] - 1);
    cur += end[node] * 2.0 * sub[node];
    for (const auto& it : to[node]) {
        double there = sub[it.second] + end[it.second];
        cur += (sub[node] - there) * there;
    }

    ans += d * cur / all;
}

int main() {
    int n;
    scanf("%d", &n);
    all = n * 1.0 * (n - 1);

    char s[N + 1];
    for (int i = 0; i < n; ++i) {
        scanf(" %s", s);
        add(s);
    }

    dfs(root);

    printf("%.10lf\n", ans);
}
