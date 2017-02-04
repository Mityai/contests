
/**
 * Author: Sergey Kopeliovich (Burunduk30@gmail.com)
 * (translated from C++ by Pavel Mavrin)
 */

class SuffixTree {

    private static final int ALPHA_SIZE = 26;

    int s[], n, vn, root, suf[], dep[], size[];
    int[] edge_st, edge_len, edge_next;

    int newV(int d, int end) {
        assert (vn < suf.length);
        dep[vn] = d;
        size[vn] = end;
        return vn++;
    }

    int split(int v, int c, int i) {
        int a = v * ALPHA_SIZE + c;
        int u = newV(dep[v] + i, 0);
        int b = u * ALPHA_SIZE + s[edge_st[a] + i];
        edge_st[b] = edge_st[a] + i;
        edge_len[b] = edge_len[a] - i;
        edge_next[b] = edge_next[a];
        edge_len[a] = i;
        edge_next[a] = u;
        return u;
    }

    void create(int u, int c, int i) {
        int x = u * ALPHA_SIZE + c;
        edge_st[x] = i;
        edge_len[x] = n - i;
        edge_next[x] = newV(dep[u] + (n - i), 1);
    }

    public SuffixTree(int[] s) {
        this.s = s;
        this.n = s.length;
        int len = 1 + n * 2;
        suf = new int[len];
        dep = new int[len];
        size = new int[len];

        // compressed 2d arrays. e[i][j] -> e[i * ALPHA_SIZE + j]
        edge_st = new int[len * ALPHA_SIZE]; // edge start
        edge_len = new int[len * ALPHA_SIZE]; // edge length
        edge_next = new int[len * ALPHA_SIZE]; // edge destination

        vn = 0;
        root = newV(0, 0);

        int v = 0, cur_c = 0, cur_i = 0;
        for (int i = 0; i < n; i++) {
            if (cur_i > 0 && cur_i == edge_len[v * ALPHA_SIZE + cur_c]) {
                v = edge_next[v * ALPHA_SIZE + cur_c];
                cur_i = 0;
            }
            int c = s[i], last = -1;
            int t = edge_st[v * ALPHA_SIZE + cur_c];
            while (cur_i > 0 && s[t + cur_i] != c) {
                int w = suf[v], u = split(v, cur_c, cur_i);
                create(u, c, i);
                if (last != -1)
                    suf[last] = u;
                last = u;
                if (v == 0) {
                    t++;
                    cur_i--;
                }
                int a;
                while (cur_i > 0 && edge_len[a = w * ALPHA_SIZE + (cur_c = s[t])] <= cur_i) {
                    cur_i -= edge_len[a];
                    w = edge_next[a];
                    t += edge_len[a];
                }
                v = w;
                if (cur_i == 0)
                    suf[last] = v;
            }
            if (cur_i > 0) {
                cur_i++;
            } else {
                cur_i = 1;
                cur_c = c;
                while (edge_len[v * ALPHA_SIZE + c] < cur_i) {
                    create(v, c, i);
                    if (v > 0)
                        v = suf[v];
                    else
                        cur_i = 0;
                }
            }
        }
    }
}

