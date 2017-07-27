#include <bits/stdc++.h>
using namespace std;

const int L = 256;

inline int good(int x, int n) {
    x %= n;
    if (x < 0) x += n;
    return x;
}

vector<int> getSuffixArray(const string& s) {
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
			tmp[buck[classes[good(sa[i] - l, n)]]++] = good(sa[i] - l, n);
		}

		sa = tmp;
		tmp[sa[0]] = 0;
		for (int i = 1; i < n; i++) {
			tmp[sa[i]] = tmp[sa[i - 1]] + (classes[sa[i]] != classes[sa[i - 1]] || classes[good(sa[i] + l, n)] != classes[good(sa[i - 1] + l, n)]);
		}
		cn = tmp[sa[n - 1]] + 1;
		classes = tmp;
	}

	return sa;
}

vector<int> getLCP(const string& s, const vector<int>& sa) {
    int n = s.length();
    vector<int> rev(n);
    vector<int> lcp(n);
    for (int i = 0; i < n; ++i) {
        rev[sa[i]] = i;
    }
    int cur = 0;
    for (int i = 0; i < n - 1; ++i) {
        while (i + cur < n&& rev[i] + 1 < n && sa[rev[i] + 1] < n &&
                s[i + cur] == s[sa[rev[i] + 1] + cur]) {
            ++cur;
        }
        lcp[rev[i]] = cur--;
        cur = max(0, cur);
    }
    return lcp;
}

int main() {
    freopen("array.in", "r", stdin);
    freopen("array.out", "w", stdout);

    string s;
    cin >> s;

    s += "$";

    auto sa = getSuffixArray(s);
    auto lcp = getLCP(s, sa);

    for (size_t i = 1; i < sa.size(); ++i) {
        printf("%d ", sa[i] + 1);
    }
    puts("");
    for (size_t i = 1; i < int(lcp.size()) - 1; ++i) {
        printf("%d ", lcp[i]);
    }
    puts("");
}
