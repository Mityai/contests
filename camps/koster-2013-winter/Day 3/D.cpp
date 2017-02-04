#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <cstdio>
#include <cmath>
#include <vector>
#include <string>
#include <map>
using namespace std;
 
int main() {
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    
    int n, m, p;
    cin >> n >> m >> p;
    vector<pair<string, int> > f, s;
    map<int, string> sl;
    for (int i = 0; i < n; i++) {
        string temp;
        cin >> temp;
        if (i%2) {
            f.push_back(make_pair(temp, i));
            sl[i] = temp;
        } else {
            s.push_back(make_pair(temp, i));
            sl[i] = temp;
        }
    }
    vector<pair<int, int> > f_in, s_in;
    for (int i = 0; i < p; i++) {
        f_in.push_back(make_pair(0, f[i].second));
        s_in.push_back(make_pair(0, s[i].second));
    }
    vector<pair<int, int> > f_out, s_out;
    for (int i = p; i < f.size() || i < s.size(); i++) {
        if (i < f.size()) f_out.push_back(make_pair(0, f[i].second));
        if (i < s.size()) s_out.push_back(make_pair(0, s[i].second));
    }
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < f_in.size(); j++) {
            f_in[j].first++;
            s_in[j].first++;
        }
        vector<pair<int, int> >::iterator it_mxf_i = max_element(f_in.begin(), f_in.end());
        vector<pair<int, int> >::iterator it_mxs_i = max_element(s_in.begin(), s_in.end());
        pair<int, int> mxf_in = *it_mxf_i;
        pair<int, int> mxs_in = *it_mxs_i;
        f_in.erase(it_mxf_i);
        s_in.erase(it_mxs_i);

        vector<pair<int, int> >::iterator it_mnf_i = min_element(f_out.begin(), f_out.end());
        vector<pair<int, int> >::iterator it_mns_i = min_element(s_out.begin(), s_out.end());
        pair<int, int> mnf_in = *it_mnf_i;
        pair<int, int> mns_in = *it_mns_i;
        f_out.erase(it_mnf_i);
        s_out.erase(it_mns_i);

        f_in.push_back(mnf_in);
        s_in.push_back(mns_in);

        f_out.push_back(mxf_in);
        s_out.push_back(mxs_in);
    }
    vector<string> ans;
    for (int i = 0; i < f_in.size(); i++) {
        ans.push_back(sl[f_in[i].second]);
    }
    for (int i = 0; i < s_in.size(); i++) {
        ans.push_back(sl[s_in[i].second]);
    }
    sort(ans.begin(), ans.end());
    for (int i = 0; i < ans.size(); i++) {
        cout << ans[i] << " ";
    }

    return 0;
}