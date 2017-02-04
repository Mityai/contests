#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <vector>
#include <algorithm>
#define ll long long
using namespace std;

int main() {
    freopen("gold.in", "r", stdin);
    freopen("gold.out", "w", stdout);

    ll k, T, S, N;
    cin >> k >> T >> S >> N;
    ll c = 1;
    vector<ll> build(N+1);
    ll ans = 0;
    for (int i = 1; i <= N; i++) {
    	if (S < k * (N - (i + T) + 1)) {
    		build[i + T] = ans / S;
    		ans -= (ans / S) * S;
    	}
    	c += build[i];     
    	ans += c*k;
    }
    cout << ans;

    return 0;
}