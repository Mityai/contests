#include <bits/stdc++.h>

#define fi first
#define se second
#define mp make_pair;

using namespace std;

const int MAXN = 1e5;
const int MAXK = 3200;

struct Segment {
    vector<int> a;
    vector<int> b;

    Segment() {}
    Segment(const vector<int> &_a) {
        a = _a;
        b = _a;
        sort(b.begin(), b.end());
    }
};

vector<Segment*> block;

void add(int i, int x) {
    int sum = 0;
    int j = 0;
    while (j < block.size() && sum + (block[j]->a).size() < i) {
        sum += (block[j]->a).size();
        j++;
    }
    if (j == block.size()) --j;

    i -= sum;
    (block[j]->a).insert((block[j]->a).begin() + i, x);

    int l = -1, r = (int)(block[j]->b).size();
    while (l + 1 < r) {
        int m = (l + r) / 2;
        if ((block[j]->b)[m] <= x) {
            l = m;
        } else {
            r = m;
        }
    }
    (block[j]->b).insert((block[j]->b).begin() + r, x);
}

void del(int i) {
    int sum = 0;
    int j = 0;
    while (sum + (block[j]->a).size() <= i) {
        sum += (block[j]->a).size();
        j++;
    }

    i -= sum;

    int x = (block[j]->a)[i];
    (block[j]->a).erase((block[j]->a).begin() + i);

    for (int k = 0; k < (int)(block[j]->b).size(); k++) {
        if ((block[j]->b)[k] == x) {
            (block[j]->b).erase((block[j]->b).begin() + k);
            break;
        }
    }
};

int sum(int l, int r, int x) {
    int j1 = 0;
    int li;
    {
        int sum = 0;
        while (sum + (block[j1]->a).size() <= l) {
            sum += (block[j1]->a).size();
            j1++;
        }

        li = l - sum;
    }

    int j2 = 0;
    int ri;
    {
        int sum = 0;
        while (sum + (block[j2]->a).size() <= r) {
            sum += (block[j2]->a).size();
            j2++;
        }
        ri = r - sum;
    }

    int res = 0;
    if (j1 == j2) {
        for (int k = li; k <= ri; k++) {
            if ((block[j1]->a)[k] <= x) {
                res++;
            }
        }
    } else {
        for (int k = li; k < (int)(block[j1]->a).size(); k++) {
            if ((block[j1]->a)[k] <= x) {
                res++;
            }
        }
        for (int k = 0; k <= ri; k++) {
            if ((block[j2]->a)[k] <= x) {
                res++;
            }
        }
        for (int j = j1 + 1; j <= j2 - 1; j++) {
            int lb = -1, rb = (int)(block[j]->b).size();
            while (lb + 1 < rb) {
                int mb = (lb + rb) / 2;
                if ((block[j]->b)[mb] <= x) {
                    lb = mb;
                } else {
                    rb = mb;
                }
            }
            res += rb;
        }
    }

    return res;
}

int sz;

void rebuild() {
    vector<int> cur(sz);
    for (int i = 0, j = 0; i < block.size(); i++) {
        for (int k = 0; k < (block[i]->a).size(); k++) {
            cur[j++] = (block[i]->a)[k];
        }
    }
    block.clear();

    vector<int> curvect;
    for (int i = 0; i < sz; i++) {
        curvect.push_back(cur[i]);
        if ((i % MAXK == 0 && i != 0) || i == sz - 1) {
            block.push_back(new Segment(curvect));
            curvect.clear();
        }
    }
}

int main() {
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);

    int n;
    scanf("%d", &n);

    sz = n;

    vector<int> curvect;
    for (int i = 0; i < n; i++) {
        int x;
        scanf("%d", &x);

        curvect.push_back(x);
        if ((i % MAXK == 0 && i != 0) || i == n - 1) {
            block.push_back(new Segment(curvect));
            curvect.clear();
        }
    }

    char c;
    for (int ii = 0; scanf(" %c", &c) == 1; ii++) {
        if (c == '+') {
            int i, x;
            scanf("%d%d", &i, &x);

            add(i, x);
            sz++;
        } else if (c == '-') {
            int i;
            scanf("%d", &i);

            del(i);
            sz--;
        } else if (c == '?') {
            int l, r, x;
            scanf("%d%d%d", &l, &r, &x);

            printf("%d\n", sum(l, r, x));
        }

        if (ii != 0 && ii % MAXK == 0) {
            rebuild();
        }
        //cout << block.size() << endl;
    }
}
