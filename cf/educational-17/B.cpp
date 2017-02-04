#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ios_base::sync_with_stdio(false);

    int a, b, c;
    cin >> a >> b >> c;

    int m;
    cin >> m;

    vector<int> usb, ps2;
    for (int i = 0; i < m; ++i) {
        int val;
        string t;
        cin >> val >> t;

        if (t[0] == 'U') {
            usb.push_back(val);
        } else {
            ps2.push_back(val);
        }
    }

    sort(usb.begin(), usb.end());
    sort(ps2.begin(), ps2.end());
    int k1 = 0, k2 = 0;

    ll sum = 0;
    for (int i = 0; i < a; ++i) {
        if (k1 < usb.size()) {
            sum += usb[k1++];
        } else {
            break;
        }
    }

    for (int i = 0; i < b; ++i) {
        if (k2 < ps2.size()) {
            sum += ps2[k2++];
        } else {
            break;
        }
    }

    for (int i = 0; i < c; ++i) {
        if (k1 < usb.size() && k2 < ps2.size()) {
            if (usb[k1] < ps2[k2]) {
                sum += usb[k1++];
            } else {
                sum += ps2[k2++];
            }
        } else if (k1 < usb.size()) {
            sum += usb[k1++];
        } else if (k2 < ps2.size()) {
            sum += ps2[k2++];
        } else {
            break;
        }
    }

    cout << k1 + k2 << ' ' << sum << endl;
}
