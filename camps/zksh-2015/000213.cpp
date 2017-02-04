#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

typedef long long ll;

bool cmp(string s1, string s2) {
	string t1 = s1 + s2;
	string t2 = s2 + s1;
	for (int i = 0; i < t1.length(); i++) {
		if (t1[i] > t2[i]) return true;
		if (t1[i] < t2[i]) return false;
	}
	return false;
}

int main() {
#if __APPLE__
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);	
#else
	freopen("number.in", "r", stdin);
	freopen("number.out", "w", stdout);	
#endif

	vector<string> s;
	string t;
	while (cin >> t) {
		s.push_back(t);
	}

	sort(s.begin(), s.end(), cmp);
	for (int i = 0; i < (int)s.size(); i++) {
		cout << s[i];
	}
}
