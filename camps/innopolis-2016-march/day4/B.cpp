#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;
 
typedef long long ll;

int main() {
    freopen("shopping.dat", "r", stdin);
    freopen("shopping.sol", "w", stdout);
 
    int n;
    while (scanf("%d", &n) == 1) {
        vector<int> q;
        int mxA = 0;
        int a[n];
        for (int i = 0; i < n; i++) {
            scanf("%d", a + i);
            q.push_back(a[i]);
            mxA = max(mxA, a[i]);
        }
        int mxB = 0;
        int b[n];
        for (int i = 0; i < n; i++) {
            scanf("%d", b + i);
            q.push_back(b[i]);
            mxB = max(mxB, b[i]);
        }
        int mxmn = min(mxA, mxB);

        if (n == 1) {
            printf("%d\n", mxmn);
            continue;
        }

        sort(q.begin(), q.end());
        q.erase(unique(q.begin(), q.end()), q.end());

        map< int, vector<int> > posa, posb;

        for (int i = 0; i < n; i++) {
            posa[a[i]].push_back(i);
            posb[b[i]].push_back(i);
        }

        bool useda[n], usedb[n];
        memset(useda, 0, sizeof useda);
        memset(usedb, 0, sizeof usedb);
        int lefta[n], righta[n];
        int leftb[n], rightb[n];
        ll ans = 0;
        for (int i = (int)q.size() - 1, mxa = 0, mxb = 0; i >= 0; i--) {
            int h = q[i];
            for (int pos : posa[h]) {
                lefta[pos] = righta[pos] = pos;
                if (pos == 0) {
                    if (useda[pos + 1]) {
                        righta[pos] = righta[pos + 1];
                        lefta[righta[pos]] = pos;
                        mxa = max(mxa, righta[pos] - pos + 1);
                    }
                } else if (pos == n - 1) {
                    if (useda[pos - 1]) {
                        lefta[pos] = lefta[pos - 1];
                        righta[lefta[pos]] = pos;
                        mxa = max(mxa, pos - lefta[pos] + 1);
                    }
                } else {
                    if (useda[pos - 1] && useda[pos + 1]) {
                        righta[lefta[pos - 1]] = righta[pos + 1];
                        lefta[righta[pos + 1]] = lefta[pos - 1];
                        mxa = max(mxa, righta[pos + 1] - lefta[pos - 1] + 1);
                    } else if (useda[pos - 1]) {
                        lefta[pos] = lefta[pos - 1];
                        righta[lefta[pos]] = pos;
                        mxa = max(mxa, pos - lefta[pos] + 1);
                    } else if (useda[pos + 1]) {
                        righta[pos] = righta[pos + 1];
                        lefta[righta[pos]] = pos;
                        mxa = max(mxa, righta[pos] - pos + 1);
                    }
                }
                mxa = max(mxa, 1);
                useda[pos] = true;
            }
            for (int pos : posb[h]) {
                leftb[pos] = rightb[pos] = pos;
                if (pos == 0) {
                    if (usedb[pos + 1]) {
                        rightb[pos] = rightb[pos + 1];
                        leftb[rightb[pos]] = pos;
                        mxb = max(mxb, rightb[pos] - pos + 1);
                    }
                } else if (pos == n - 1) {
                    if (usedb[pos - 1]) {
                        leftb[pos] = leftb[pos - 1];
                        rightb[leftb[pos]] = pos;
                        mxb = max(mxb, pos - leftb[pos] + 1);
                    }
                } else {
                    if (usedb[pos - 1] && usedb[pos + 1]) {
                        rightb[leftb[pos - 1]] = rightb[pos + 1];
                        leftb[rightb[pos + 1]] = leftb[pos - 1];
                        mxb = max(mxb, rightb[pos + 1] - leftb[pos - 1] + 1);
                    } else if (usedb[pos - 1]) {
                        leftb[pos] = leftb[pos - 1];
                        rightb[leftb[pos]] = pos;
                        mxb = max(mxb, pos - leftb[pos] + 1);
                    } else if (usedb[pos + 1]) {
                        rightb[pos] = rightb[pos + 1];
                        leftb[rightb[pos]] = pos;
                        mxb = max(mxb, rightb[pos] - pos + 1);
                    }
                }
                mxb = max(mxb, 1);
                usedb[pos] = true;
            }
            //printf("mxa = %d mxb = %d h = %d\n", mxa, mxb, h);
            ans = max(ans, (ll)mxa * mxb * h);
        }

        printf("%lld\n", ans);
    }
}
