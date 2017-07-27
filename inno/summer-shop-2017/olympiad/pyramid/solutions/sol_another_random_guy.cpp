/*
ID: 5ak0
PROG:
LANG: C++11
*/
 
#include <bits/stdc++.h>
#define fr first
#define sc second
#define pb push_back
#define mpr make_pair
 
using namespace std;
 
typedef long long ll;
typedef pair<int, int> pii;
const int INF = 1e9 + 7;
 
int n;
vector <int> p, v;
 
pii f(vector<int> v){
	pii ret = {1, 0};
	for (int i = 1; i < v.size(); ++i)
        if (v[i] == v[i - 1])
            ret.fr = false;
	if (!ret.fr)
        return ret;
	ret.second = (v[n / 2] ^ ((n / 2) & 1));
	return ret;
}
 
int check(int val){
	v.clear();
	for (int i = 0; i <= n; ++i){
		int value;
		if (p[i] >= val)
            value = 1;
		else
            value = 0;
		v.pb(value);
	}
	pii ret = f(v);
	if (ret.first)
        return ret.second;
 
	int lp = -1;
	int rp = -1;
	for (int i = n / 2 + 1; i >= 1; --i)
        if (v[i] == v[i - 1]){
            lp = i;
            break;
        }
	for (int i = n / 2; i <= n - 1; ++i)
        if(v[i] == v[i + 1]){
            rp = i;
            break;
        }
	int addLp = 0, addRp = 0;
	if (lp == -1 || rp == -1){
		if(lp == -1)
            return v[rp];
		else
            return v[lp];
	}
	else{
		if (v[lp] == v[rp])
            return v[lp];
		for (int i = lp + 1; i <= rp; ++i)
            if(v[i] == v[lp])
                ++addLp;
            else
                --addRp;
	}
	if (lp + addLp >= n / 2)
        return v[lp];
	else
        return v[rp];
}
 
int main(){
    #ifndef SAKO
    //freopen(".in", "r", stdin);
    //freopen(".out", "w", stdout);
    #endif // SAKO
    ios_base::sync_with_stdio(0);
 
 
	cin >> n;
	n = n + n - 1;
	for (int i = 1; i <= n; ++i){
		int x;
		cin >> x;
		p.pb(x);
	}
	int l = 0, r = n + 1;
	while (r - l > 1){
		int m = (l + r) / 2;
		if (check(m))
            l = m;
		else
            r = m;
	}
	cout << l;
    return 0;
}
