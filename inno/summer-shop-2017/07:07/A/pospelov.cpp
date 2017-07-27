#include <bits/stdc++.h>
  
#define FN "flow"
  
using namespace std;
  
typedef long long ll;
  
const int MAXN = (int)110;
const int MAXM = (int)5100;
const int INF = (int)1e9;
  
struct edges
{
    int num;
    vector <vector <int>> g;
    vector <int> cap;
    vector <int> flow;
    vector <int> to;
  
    edges(int n, int m)
    {
        g.resize(n);
        to.resize(2 * m);
        cap.resize(2 * m);
        flow.resize(2 * m);
        num = 0;
    }
    void addEdge(int u, int v, int c)
    {
        g[u].push_back(num);
        cap[num] = c;
        to[num] = v;
        g[v].push_back(num ^ 1);
        cap[num ^ 1] = c;
        to[num ^ 1] = u;
        num += 2;
    }
    void updateEdge(int eNum, int newFlow)
    {
        flow[eNum] += newFlow;
        flow[eNum ^ 1] -= newFlow;
    }
    int getPossibleFlow(int eNum)
    {
        return cap[eNum] - flow[eNum];
    }
};
  
edges graph(MAXN, MAXM);
vector <int> prv(MAXN);
  
int push(int s, int t, int curFlow)
{
    queue <int> q;
    q.push(s);
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        for (auto e : graph.g[u])
        {
            int v = graph.to[e];
            if (prv[v] == -1 && graph.getPossibleFlow(e) > 0)
            {
                prv[v] = e ^ 1;
                q.push(v);
            }
        }
    }
    if (prv[t] == -1)
        return 0;
    int cur = t;
    while (cur != 1)
    {
        curFlow = min(curFlow, graph.getPossibleFlow(prv[cur] ^ 1));
        cur = graph.to[prv[cur]];
    }
    cur = t;
    while (cur != 1)
    {
        graph.updateEdge(prv[cur] ^ 1, curFlow);
        cur = graph.to[prv[cur]];
    }
    return curFlow;
}
  
signed main()
{
#ifdef PC
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
#ifndef PC
    freopen(FN".in", "r", stdin);
    freopen(FN".out", "w", stdout);
#endif
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        graph.addEdge(u, v, w);
    }
      
    int flow = 0;
    int curFlow = 0;
    fill(prv.begin(), prv.end(), -1);
    while ((curFlow = push(1, n, INF)) > 0)
    {
        flow += curFlow;
        fill(prv.begin(), prv.end(), -1);
    }
    cout << flow << "\n";
    for (int i = 0; i < m; i++)
        cout << graph.flow[i * 2] << "\n";
    return 0;
}
