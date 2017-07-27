#include <bits/stdc++.h>
 
#define f_name "mail"
 
using namespace std;
 
typedef long long ll;
 
const int B_SIZE = 1500;
const ll MOD = (int)1e9;
const int MAXN = (int)3e5 + 4;
 
vector <ll> blocks(MAXN);
vector <ll> pre(MAXN);
unordered_map <int, bool> used;
 
int num;
 
inline void add(int x)
{
    if (used.find(x) != used.end())
        return;
    used[x] = 1;
    blocks[num++] = x;
    if (num % B_SIZE == 0)
    {
        stable_sort(blocks.begin(), blocks.end());
        for (int i = 1; i < blocks.size(); i++)
            pre[i] = pre[i - 1] + blocks[i];
    }
}
 
inline ll get(int l, int r)
{
    ll val = 0;
    int l1 = 0, r1 = num / B_SIZE * B_SIZE, m1;
    while (l1 + 1 < r1)
    {
        m1 = (l1 + r1) / 2;
        if (blocks[m1] > r)
            r1 = m1;
        else
            l1 = m1;
    }
 
    int l2 = 0, r2 = l1, m2;
    while (l2 + 1 < r2)
    {
        m2 = (l2 + r2) / 2;
        if (blocks[m2] < l)
            l2 = m2;
        else
            r2 = m2;
    }
 
    if (l <= blocks[l1] && blocks[l1] <= r)
        val += pre[l1] - pre[l2];
 
    for (int i = num / B_SIZE * B_SIZE; i < blocks.size(); i++)
        if (l <= blocks[i] && blocks[i] <= r)
            val += blocks[i];
 
    return val;
}
 
int main()
{
#ifdef PC
    freopen("in.txt", "r", stdin);
#endif
    add(0);
    int n;
    scanf("%d", &n);
    ll prev = -1;
    for (int i = 0; i < n; i++)
    {
        char type;
        scanf(" %c", &type);
        if (type == '+')
        {
            ll x;
            scanf("%lld", &x);
            add((x + (prev == -1 ? 0 : prev)) % MOD);
            prev = -1;
        }
        else
        {
            int l, r;
            scanf("%d%d", &l, &r);
            prev = get(l, r);
            printf("%lld\n", prev);
        }
    }
 
    return 0;
}
