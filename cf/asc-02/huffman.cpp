using namespace std;

typedef long long ll;

struct Heap {
    int n;
    ll* a;

    Heap(int n) : n(n) {
        a = new ll[n];
    }

    void siftDown(int i) {
        while (2 * i + 1 < n) {
            int l = 2 * i + 1;
            int r = 2 * i + 2;
            if (r < n && a[r] < a[l]) l = r;
            if (a[i] <= a[l]) break;
            ll t = a[i];
            a[i] = a[l];
            a[l] = t;
            i = l;
        }
    }

    void siftUp(int i) {
        while (i > 0) {
            int j = (i - 1) >> 1;
            if (a[i] < a[j]) {
                ll t = a[i];
                a[i] = a[j];
                a[j] = t;
            } else break;
            i = j;
        }
    }

    ll extractMin() {
        ll ret = a[0];
        a[0] = a[--n];
        siftDown(0);
        return ret;
    }

    void insert(ll val) {
        a[n++] = val;
        siftUp(n - 1);
    }
};

int main() {
    freopen("huffman.in", "r", stdin);
    freopen("huffman.out", "w", stdout);

    int n;
    scanf("%d", &n);

    Heap q(n);
    for (int i = 0; i < n; ++i) {
        scanf("%lld", &q.a[i]);
    }

    ll ans = 0;
    while (q.n != 1) {
        ll v = q.extractMin();
        ll u = q.extractMin();
        q.insert(v + u);
        ans += v + u;
    }

    printf("%lld\n", ans);
}
