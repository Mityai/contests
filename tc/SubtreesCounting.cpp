#include <vector>
#include <assert.h>
#include <list>
#include <cstring>
#include <map>
#include <set>
#include <queue>
#include <deque>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace std;

typedef long long ll;

const int MOD = 1e9 + 7;
const int N = 1e5;

class SubtreesCounting {
public:
    vector<int> g[N];
    ll cnt[N], dp[N];

    ll binpow(ll a, ll n) {
        if (n == 0) return 1;
        if (n == 1) return a % MOD;
        ll b = binpow(a, n >> 1LL);
        b = (b * b) % MOD;
        if (n & 1LL) b = (b * a) % MOD;
        return b;
    }

    void dfs(int v, int p) {
        cnt[v] = 1;
        for (int u : g[v]) {
            if (u != p) {
                dfs(u, v);
                cnt[v] = (cnt[v] * (cnt[u] + 1)) % MOD;
                assert(cnt[v] >= 0);
            }
        }
        dp[v] = cnt[v];
        for (int u : g[v]) {
            if (u != p) {
                dp[v] = (dp[v] + (dp[u] * cnt[v]) % MOD * binpow(cnt[u] + 1, MOD - 2)) % MOD;
            }
        }
    }

	int sumOfSizes(int n, int a0, int b, int c, int m) {
        memset(dp, 0, sizeof dp);
        memset(cnt, 0, sizeof cnt);
        ll a[n];
        a[0] = a0;
        for (int i = 1; i <= n - 2; i++) {
            a[i] = (b * a[i - 1] + c) % m;
        }
        for (int i = 1; i <= n - 1; i++) {
            int j = a[i - 1] % i;
            g[i].push_back(j);
            g[j].push_back(i);
        }

        dfs(0, 0);

        int ans = 0;
        for (int i = 0; i < n; i++) {
            ans = (ans + dp[i]) % MOD;
        }
        return ans;
	}
};


// BEGIN KAWIGIEDIT TESTING
// Generated by KawigiEdit 2.1.4 (beta) modified by pivanof
bool KawigiEdit_RunTest(int testNum, int p0, int p1, int p2, int p3, int p4, bool hasAnswer, int p5) {
	cout << "Test " << testNum << ": [" << p0 << "," << p1 << "," << p2 << "," << p3 << "," << p4;
	cout << "]" << endl;
	SubtreesCounting *obj;
	int answer;
	obj = new SubtreesCounting();
	clock_t startTime = clock();
	answer = obj->sumOfSizes(p0, p1, p2, p3, p4);
	clock_t endTime = clock();
	delete obj;
	bool res;
	res = true;
	cout << "Time: " << double(endTime - startTime) / CLOCKS_PER_SEC << " seconds" << endl;
	if (hasAnswer) {
		cout << "Desired answer:" << endl;
		cout << "\t" << p5 << endl;
	}
	cout << "Your answer:" << endl;
	cout << "\t" << answer << endl;
	if (hasAnswer) {
		res = answer == p5;
	}
	if (!res) {
		cout << "DOESN'T MATCH!!!!" << endl;
	} else if (double(endTime - startTime) / CLOCKS_PER_SEC >= 2) {
		cout << "FAIL the timeout" << endl;
		res = false;
	} else if (hasAnswer) {
		cout << "Match :-)" << endl;
	} else {
		cout << "OK, but is it right?" << endl;
	}
	cout << "" << endl;
	return res;
}
int main() {
	bool all_right;
	all_right = true;
	
	int p0;
	int p1;
	int p2;
	int p3;
	int p4;
	int p5;
	
	{
	// ----- test 0 -----
	p0 = 3;
	p1 = 1;
	p2 = 1;
	p3 = 1;
	p4 = 1;
	p5 = 10;
	all_right = KawigiEdit_RunTest(0, p0, p1, p2, p3, p4, true, p5) && all_right;
	// ------------------
	}
	
	{
	// ----- test 1 -----
	p0 = 5;
	p1 = 1;
	p2 = 2;
	p3 = 3;
	p4 = 100;
	p5 = 52;
	all_right = KawigiEdit_RunTest(1, p0, p1, p2, p3, p4, true, p5) && all_right;
	// ------------------
	}
	
	{
	// ----- test 2 -----
	p0 = 1;
	p1 = 1;
	p2 = 1;
	p3 = 1;
	p4 = 1;
	p5 = 1;
	all_right = KawigiEdit_RunTest(2, p0, p1, p2, p3, p4, true, p5) && all_right;
	// ------------------
	}
	
	{
	// ----- test 3 -----
	p0 = 2;
	p1 = 5;
	p2 = 6;
	p3 = 7;
	p4 = 8;
	p5 = 4;
	all_right = KawigiEdit_RunTest(3, p0, p1, p2, p3, p4, true, p5) && all_right;
	// ------------------
	}
	
	{
	// ----- test 4 -----
	p0 = 100000;
	p1 = 123;
	p2 = 46645;
	p3 = 4564579;
	p4 = 1000000000;
	p5 = 769840633;
	all_right = KawigiEdit_RunTest(4, p0, p1, p2, p3, p4, true, p5) && all_right;
	// ------------------
	}
	
	if (all_right) {
		cout << "You're a stud (at least on the example cases)!" << endl;
	} else {
		cout << "Some of the test cases had errors." << endl;
	}
	return 0;
}
// END KAWIGIEDIT TESTING
//Powered by KawigiEdit 2.1.4 (beta) modified by pivanof!
