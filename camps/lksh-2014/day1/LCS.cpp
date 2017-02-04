#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <cmath>

typedef long long ll;

using namespace std;

int main() {
    freopen("lcs2.in", "r", stdin);
    freopen("lcs2.out", "w", stdout);

    string s1, s2;
    cin >> s1 >> s2;

    int n = s1.length(), m = s2.length();

    vector<vector<int> > d(n + 1, vector<int> (m + 1));

    int lasti = 0, lastj = 0;
    for (int i = 1; i <= n; i++) {
    	for (int j = 1; j <= m; j++) {
    		if (s1[i - 1] == s2[j - 1]) {
    			d[i][j] = d[i - 1][j - 1] + 1;
    		} else {
    			d[i][j] = max(d[i - 1][j], d[i][j - 1]);
    		}
    	}
    }

    string ans;
    int i = n, j = m;
    while (d[i][j] != 0) {
    	if (d[i][j] != d[i - 1][j - 1] && d[i][j] != d[i - 1][j] && d[i][j] != d[i][j - 1]) {
    		ans += s1[i - 1];
    		
    		--i;
    		--j;
    	} else {
    		while (d[i - 1][j] == d[i][j]) {
    			--i;
    		}

    		while (d[i][j - 1] == d[i][j]) {
    			--j;
    		}
    	}
    }

    for (int i = ans.length() - 1; i >= 0; i--) {
    	cout << ans[i];
    }
}