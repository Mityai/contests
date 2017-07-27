#include<bits/stdc++.h>
#define mp make_pair
#define pb push_back
using namespace std;     
int n, m;
map< pair < int, int >, vector < pair<int, int> > > g;
map<pair<int, int>, int> d, cnt, used, deg;
queue< pair<int, int> > q;
int main() {
    freopen("game.in", "r", stdin);
    freopen("game.out", "w", stdout);
    cin >> n >> m;
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= m; j++) {
            int x;
            cin >> x;
            pair<int, int> a = mp(i + x, j), b = mp(i, j + x), c = mp(i, j);  
            if(x > 0 && i + x <= n) {
                g[a].pb(c);
                deg[c]++;         
            }   
            if(x > 0 && j + x <= m) {
                g[b].pb(c);
                deg[c]++;
            }
            if(x <= 0 && i + x >= 1) {
                g[a].pb(c);
                deg[c]++;
            }
            if(x <= 0 && j + x >= 1) {
                g[b].pb(c);
                deg[c]++;
            }
            if((x > 0 && i + x > n && j + x > m) || (x <= 0 && i + x < 1 && j + x < 1))
                used[c] = 1, d[c] = 1, q.push(c);           
        }
    int xx, yy;
    cin >> xx >> yy;
    pair<int, int> f = make_pair(xx, yy), a = make_pair(2, 2), b = make_pair(1, 3);
    while(!q.empty()) {
        pair<int, int> v = q.front();
        q.pop();
        //cout << v.first << " " << v.second << " asd\n";
        if(d[v] == 1) {
            for(int i = 0 ; i < g[v].size(); i++) {
                pair<int, int> to = g[v][i];
                if(!used[to]) {
                    d[to] = 2, used[to] = 1, q.push(to);
                }       
            }
        }
        else if(d[v] == 2) {
            for(int i = 0; i < g[v].size(); i++) {
                pair<int, int> to = g[v][i];
                cnt[to]++;
                if(cnt[to] == deg[to] && !used[to]) {
                    d[to] = 1;
                    used[to] = 1;
                    q.push(to);
                }   
            }           
        }
    }
    if(d[f] == 2)
        cout << "Anton";
    else if(!used[f])
        cout << "draw"; 
    else
        cout << "Yasha";
}