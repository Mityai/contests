#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int INF = 1234567890;
const int K = 52;
const int N = 2 * K + 2;
const int M = 2 * (2 + N * N);
const int s = N - 2, t = N - 1;

int n, edgeID[N], phi[N];
int to[M], cap[M], flow[M], weight[M];
vector<int> E[N];

int numEdge[N][N];

int e = 0;
void addEdge(int v, int u, int c, int w) {
    E[v].push_back(e);
    E[u].push_back(e ^ 1);
    to[e] = u;
    to[e ^ 1] = v;
    cap[e] = c;
    cap[e ^ 1] = 0;
    weight[e] = w;
    weight[e ^ 1] = -w;
    e += 2;
}

bool findShortestPath() {
    vector<int> d(N, INF);
    d[s] = 0;

    vector<char> mark(N, false);
    
    for (int i = 0; i < N; i++) {
        int v = -1;
        for (int j = 0; j < N; j++) {
            if (mark[j] == false && (v == -1 || d[v] > d[j])) {
                v = j;
            }
        }
        if (d[v] == INF) break;
        mark[v] = true;

        for (int edge : E[v]) {
            if (flow[edge] == cap[edge]) continue;
            int u = to[edge];
            int w = weight[edge];
            if (mark[u] == false && d[u] > d[v] + w + phi[v] - phi[u]) {
                d[u] = d[v] + w + phi[v] - phi[u];
                edgeID[u] = edge;
            }
        }
    }

    for (int i = 0; i < N; i++) {
        phi[i] += d[i];
    }

    return d[t] != INF;
}

int getNum(char c) {
    if ('A' <= c && c <= 'Z') return K / 2 + c - 'A';
    return c - 'a';
}

char getChar(int v) {
    if (v >= K / 2) return char('A' + v - K / 2);
    return char('a' + v);
}

int main() {
#if __APPLE__
    freopen("input.txt", "r", stdin);
#else
    //freopen("assignment.in", "r", stdin);
    //freopen("assignment.out", "w", stdout);
#endif

    ios_base::sync_with_stdio(false);

    int n, k;
    cin >> n >> k;

    string prob_answers, actual_answers;
    cin >> prob_answers >> actual_answers;

    set<int> alphabet;
    for (int i = 0; i < K; i++) {
        alphabet.insert(i);
        addEdge(s, i, 1, 0);
        addEdge(K + i, t, 1, 0);
    }

    memset(numEdge, -1, sizeof numEdge);
    for (int i = 0; i < n; i++) {
        int v = getNum(prob_answers[i]);
        int u = K + getNum(actual_answers[i]);
        if (numEdge[v][u] == -1) {
            numEdge[v][u] = e;
            addEdge(v, u, 1, -1);
        } else {
            weight[numEdge[v][u]]--;
            weight[numEdge[v][u] ^ 1]++;
        }
    }

    int ans_cost = 0;
    while (findShortestPath()) {
        int add_flow = INF;
        for (int v = t; v != s; v = to[edgeID[v] ^ 1]) {
            add_flow = min(add_flow, cap[edgeID[v]] - flow[edgeID[v]]);
        }
        for (int v = t; v != s; v = to[edgeID[v] ^ 1]) {
            flow[edgeID[v]] += add_flow;
            flow[edgeID[v] ^ 1] -= add_flow;
            ans_cost += add_flow * weight[edgeID[v]];
        }
    }

    cout << abs(ans_cost) << endl;
    vector<char> ans(k, false);
    for (int i = 0; i < k; i++) {
        bool printed = false;
        for (int edge : E[i]) {
            if (!(edge & 1) && flow[edge] == cap[edge]) {
                printed = true;
                char c = getChar(to[edge] - K);
                ans[i] = c;
                alphabet.erase(to[edge] - K);
                break;
            }
        }
    }
    for (int i = 0; i < k; i++) {
        if (ans[i] == false) {
            cout << getChar(*alphabet.begin());
            alphabet.erase(alphabet.begin());
        } else {
            cout << ans[i];
        }
    }
    cout << endl;
}
