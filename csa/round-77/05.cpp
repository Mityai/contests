#include <bits/stdc++.h>
using namespace std;

const int N = 3e4;
const int K = 200;

struct R {
    int i, j;
};

struct Q {
    int r1, c1, r2, c2;
    int i;
};

struct Fenw {
    vector<int> fenw;

    Fenw() {
        fenw.resize(N);
    }

    void add(int pos, int val) {
        for (int i = pos; i < N; i = (i | (i + 1))) {
            fenw[i] += val;
        }
    }

    int sum(int pos) {
        int res = 0;
        for (int i = pos; i >= 0; i = (i & (i + 1)) - 1) {
            res += fenw[i];
        }
        return res;
    }

    int sum(int l, int r) {
        int res = sum(r);
        if (l > 0) res -= sum(l - 1);
        return res;
    }
};

bool cmp_by_right_c(const Q& lhs, const Q& rhs) {
    return lhs.c2 < rhs.c2;
}

bool cmp_by_right_r(const Q& lhs, const Q& rhs) {
    return lhs.r2 < rhs.r2;
}

bool cmp_rooks_j(const R& lhs, const R& rhs) {
    return lhs.j < rhs.j;
}

int main() {
#if __APPLE__
    freopen("05.in", "r", stdin);
    freopen("05.out", "w", stdout);
#endif

    int n, m, k, q;
    scanf("%d%d%d%d", &n, &m, &k, &q);

    vector<R> rooks(k);
    for (auto& rook : rooks) {
        scanf("%d%d", &rook.i, &rook.j);
        --rook.i, --rook.j;
    }

    vector<Q> reqs(q);
    int it = 0;
    for (auto& req : reqs) {
        scanf("%d%d%d%d", &req.r1, &req.c1, &req.r2, &req.c2);
        --req.r1, --req.c1, --req.r2, --req.c2;
        req.i = it++;
    }

    vector<int> ans(q);
    vector<int> qwe(q);

    map<int, vector<R>> sorted_rooks;
    for (const auto& rook : rooks) {
        sorted_rooks[rook.j].push_back(rook);
    }

    vector<vector<Q>> sorted((N + K - 1) / K);
    for (const auto& req : reqs) {
        sorted[req.c1 / K].push_back(req);
    }
    for (int i = 0; i < sorted.size(); ++i) {
        auto& sreqs = sorted[i];
        sort(sreqs.begin(), sreqs.end(), cmp_by_right_c);
        Fenw fenw;
        int l = i * K, r = i * K;
        multiset<int> cnts;
        for (int j = 0; j < sreqs.size(); ++j) {
            auto& sreq = sreqs[j];
            while (r <= sreq.c2) {
                for (const auto& rook : sorted_rooks[r]) {
                    cnts.insert(rook.i);
                    if (cnts.count(rook.i) == 1) {
                        fenw.add(rook.i, 1);
                    }
                }
                ++r;
            }
            while (l > sreq.c1) {
                --l;
                for (const auto& rook : sorted_rooks[l]) {
                    cnts.insert(rook.i);
                    if (cnts.count(rook.i) == 1) {
                        fenw.add(rook.i, 1);
                    }
                }
            }
            while (l < sreq.c1) {
                for (const auto& rook : sorted_rooks[l]) {
                    cnts.erase(cnts.find(rook.i));
                    if (cnts.count(rook.i) == 0) {
                        fenw.add(rook.i, -1);
                    }
                }
                ++l;
            }

            int diff = fenw.sum(sreq.r1, sreq.r2);
            qwe[sreq.i] = diff;
            ans[sreq.i] += (sreq.c2 - sreq.c1 + 1) * diff;
        }
    }
    
    sorted_rooks.clear();
    for (const auto& rook : rooks) {
        sorted_rooks[rook.i].push_back(rook);
    }

    sorted.clear();
    sorted.resize((N + K - 1) / K);
    for (const auto& req : reqs) {
        sorted[req.r1 / K].push_back(req);
    }
    for (int i = 0; i < sorted.size(); ++i) {
        auto& sreqs = sorted[i];
        sort(sreqs.begin(), sreqs.end(), cmp_by_right_r);
        Fenw fenw;
        int l = i * K, r = i * K;
        multiset<int> cnts;
        for (int j = 0; j < sreqs.size(); ++j) {
            auto& sreq = sreqs[j];
            while (r <= sreq.r2) {
                for (const auto& rook : sorted_rooks[r]) {
                    cnts.insert(rook.j);
                    if (cnts.count(rook.j) == 1) {
                        fenw.add(rook.j, 1);
                    }
                }
                ++r;
            }
            while (l > sreq.r1) {
                --l;
                for (const auto& rook : sorted_rooks[l]) {
                    cnts.insert(rook.j);
                    if (cnts.count(rook.j) == 1) {
                        fenw.add(rook.j, 1);
                    }
                }
            }
            while (l < sreq.r1) {
                for (const auto& rook : sorted_rooks[l]) {
                    cnts.erase(cnts.find(rook.j));
                    if (cnts.count(rook.j) == 0) {
                        fenw.add(rook.j, -1);
                    }
                }
                ++l;
            }

            int diff = fenw.sum(sreq.c1, sreq.c2);
            ans[sreq.i] += (sreq.r2 - sreq.r1 + 1) * diff - diff * qwe[sreq.i];
        }
    }

    for (int x : ans) {
        printf("%d\n", x);
    }
}
