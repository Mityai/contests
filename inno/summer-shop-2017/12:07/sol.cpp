#define _CRT_SECURE_NO_WARNINGS
#include <set>
#include <map>
#include <queue>
#include <ctime>
#include <cmath>
#include <stack>
#include <random>
#include <bitset>
#include <string>
#include <vector>
#include <cstdio>
#include <iomanip>
#include <iostream>
#include <algorithm>
#include <functional>
#include <unordered_map>
using namespace std;
 
#define X first 
#define Y second 
 
const int MAXK = 26, MAXN = 1000000 + 100;
int sun[MAXN][MAXK], go[MAXN][MAXK], parent[MAXN], sufflink[MAXN], Ssufflink[MAXN], charToParent[MAXN];
vector<int> who[MAXN];
int in = 0;
bool isLeaf[MAXN], used[MAXN];
 
int nTnode()
{
    for (int i = 0; i < MAXK; i++)
    {
        go[in][i] = -1;
        sun[in][i] = -1;
    }
    parent[in] = -1;
    sufflink[in] = -1;
    Ssufflink[in] = -1;
    isLeaf[in] = false;
    used[in] = false;
    in++;
    return in - 1;
}
int nTnode(int A, int pere)
{
    for (int i = 0; i < MAXK; i++)
    {
        go[in][i] = sun[in][i] = -1;
    }
    parent[in] = A;
    sufflink[in] = -1;
    Ssufflink[in] = -1;
    charToParent[in] = pere;
    isLeaf[in] = false;
    used[in] = false;
    in++;
    return in - 1;
}
 
int Root = nTnode();
 
void addString(string &A, int SNum)
{
    int cur = Root;
    int tec;
    for (int i = 0; i < A.size(); i++)
    {
        tec = A[i] - 'a';
        if (sun[cur][tec] == -1)
        {
            sun[cur][tec] = nTnode(cur, tec);
        }
        cur = sun[cur][tec];
    }
    isLeaf[cur] = true;
    who[cur].push_back(SNum);
}
 
int getgo(int T, int c);
 
int getsufflink(int T)
{
    if (sufflink[T] == -1)
    {
        if (T == Root || parent[T] == Root)
        {
            sufflink[T] = Root;
        }
        else
        {
            sufflink[T] = getgo(getsufflink(parent[T]), charToParent[T]);
        }
    }
    return sufflink[T];
}
 
int getSsufflink(int T)
{
    if (Ssufflink[T] == -1)
    {
        if (isLeaf[getsufflink(T)])
        {
            Ssufflink[T] = getsufflink(T);
        }
        else if (getsufflink(T) == Root)
        {
            Ssufflink[T] = Root;
        }
        else
        {
            Ssufflink[T] = getSsufflink(getsufflink(T));
        }
    }
    return Ssufflink[T];
}
 
int getgo(int T, int c)
{
    if (go[T][c] == -1)
    {
        if (sun[T][c] != -1)
        {
            go[T][c] = sun[T][c];
        }
        else if (T == Root)
        {
            go[T][c] = Root;
        }
        else
        {
            go[T][c] = getgo(getsufflink(T), c);
        }
    }
    return go[T][c];
}
 
int answer[MAXN];
 
void read(string &s) {
    int c = getchar();
    while (c < 'a' || c > 'z') c = getchar();
    s = "";
    while (c >= 'a' && c <= 'z') {
        s += (char)c;
        c = getchar();
    }
}
 
int main()
{
#if _DEBUG
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#else
    freopen("search5.in", "r", stdin);
    freopen("search5.out", "w", stdout);
#endif
    int n;
    scanf("%d", &n);
    string s;
    for (int i = 0; i < n; i++)
    {
        read(s);
        addString(s, i);
    }
    read(s);
    for (int i = 0; i < in; i++)
    {
        getsufflink(i);
        getSsufflink(i);
    }
    int cur = Root, kok;
    for (int i = 0; i < s.size(); i++)
    {
        cur = getgo(cur, s[i] - 'a');
        kok = cur;
        while (kok != Root)
        {
            for (int i = 0; i < who[kok].size(); i++)
            {
                answer[who[kok][i]]++;
            }
            kok = Ssufflink[kok];
        }
    }
    for (int i = 0; i < n; i++)
    {
        printf("%d\n", answer[i]);
    }
    return 0;
}
