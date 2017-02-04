#include <bits/stdc++.h>
#define mp make_pair
#define fi first
#define se second
using namespace std;

typedef long long ll;

const int L = 256;

vector<int> suffixArray(string s) {
	int n = (int)s.length();
	vector<int> sa(n);
	vector<int> classes(n);
	vector<int> tmp(n);
	vector<int> buck(max(L, n));

	for (int i = 0; i < n; i++) {
		buck[s[i]]++;
	}

	int sum = 0;
	for (int i = 0; i < L; i++) {
		int t = buck[i];
		sum += t;
		buck[i] = sum - t;
	}

	for (int i = 0; i < n; i++) {
		sa[buck[s[i]]++] = i;
	}

	classes[sa[0]] = 0;
	for (int i = 1; i < n; i++) {
		classes[sa[i]] = classes[sa[i - 1]] + (s[sa[i]] != s[sa[i - 1]]);
	}

	int cn = classes[sa[n - 1]] + 1;
	for (int l = 1; l < n; l *= 2) {
		for (int i = 0; i < n; i++) {
			buck[i] = 0;
		}
		for (int i = 0; i < n; i++) {
			buck[classes[i]]++;
		}
		sum = 0;
		for (int i = 0; i < cn; i++) {
			int t = buck[i];
			sum += t;
			buck[i] = sum - t;
		}

		for (int i = 0; i < n; i++) {
			tmp[buck[classes[(sa[i] - l + n) % n]]++] = (sa[i] - l + n) % n;
		}

		sa = tmp;
		tmp[sa[0]] = 0;
		for (int i = 1; i < n; i++) {
			tmp[sa[i]] = tmp[sa[i - 1]] + (classes[sa[i]] != classes[sa[i - 1]] || classes[(sa[i] + l) % n] != classes[(sa[i - 1] + l) % n]);
		}
		cn = tmp[sa[n - 1]] + 1;
		classes = tmp;
	}

	return sa;
}

vector<int> longestCommonPrefix(string s, vector<int> sa) {
	int n = (int)s.length();
	vector<int> rev(n);
	vector<int> lcp(n);
	for(int i = 0; i < n; i++) {
		rev[sa[i]] = i;	
	}

	int cur = 0;
	for (int i = 0; i < n - 1; i++) {
		while (i + cur < n && rev[i] + 1 < n && sa[rev[i] + 1] < n && 
			   s[i + cur] == s[sa[rev[i] + 1] + cur]) {
			cur++;
		}
		lcp[rev[i]] = cur--;
		cur = max(0, cur);
	}
	return lcp;
}

int main() {
#if __APPLE__
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#else
    // freopen(".in", "r", stdin);
    // freopen(".out", "w", stdout);
#endif

	string s;
	cin >> s;
	s += '$';

	vector<int> sa = suffixArray(s);
	vector<int> lcp = longestCommonPrefix(s, sa);
	
	for (int i = 0; i < (int)s.length(); i++) {
		cout << s.substr(sa[i]) << ' ' << sa[i] << ' ' << lcp[i] << endl;
	}
}
