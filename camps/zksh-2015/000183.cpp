#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

typedef long long ll;

int main() {
#if __APPLE__
	freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);	
#endif

	string s;
	cin >> s;

	vector<int> p(s.length());
	int opi = 0;
	bool closed = true;
	for (int i = 0; i < (int)s.length(); i++) {
		if (s[i] == ')') {
			p[opi] = i;
			closed = true;
		} else if (s[i] == '(') {
			if (closed) {
             	opi = i;
				closed = false;
			}
		}
	}

	string t = "";
	for (int i = 0; i < (int)s.length(); i++) {
		if (s[i] == '(') {
			int len = p[i];
			if (len != 0) {
				for (; i <= len; i++) {
					t += '*';
				}
				i--;
			}
		} else {
			t += s[i];
		}
	}

	cout << t << endl;
}

