import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Arrays;
import java.util.Random;
import java.util.StringTokenizer;

/**
 * @author Pavel Mavrin
 */
public class longrepeat {

    private void solve() throws IOException {
        String s = next();
        SuffixArray sa = new SuffixArray(s);
        int n = s.length();
        int res = 1;
        for (int l = 1; l < n; l++) {
            for (int i = 0; i + l <= n; i += l) {
                int x = sa.lcp(i, i + l) + l;
                res = Math.max(res, x / l);
                int r = x % l;
                if (i > 0) {
                    x = sa.lcp(i - l + r, i + r) + l;
                    res = Math.max(res, x / l);
                }
            }
        }
        out.println(res);
    }

    class SuffixArray {

        String s;
        int n;

        public SuffixArray(String s) {
            s = s + (char) 0;
            this.s = s;
            n = s.length();
            c = new int[n];
            p = new int[n];
            cc = new int[n];
            pp = new int[n];
            cnt = new int[Math.max(n, 256) + 1];
            for (int i = 0; i < n; i++) {
                p[i] = i;
                c[i] = s.charAt(i);
            }
            sort();
            for (int k = 1; k < n; k *= 2) {
                for (int i = 0; i < n; i++) {
                    p[i] -= k;
                    if (p[i] < 0) p[i] += n;
                }
                sort();
                int cl = 0;
                for (int i = 0; i < n; i++) {
                    if (i > 0) {
                        int x1 = p[i - 1];
                        int y1 = p[i];
                        int x2 = x1 + k;
                        if (x2 >= n) x2 -= n;
                        int y2 = y1 + k;
                        if (y2 >= n) y2 -= n;
                        if (c[x1] < c[y1] || c[x1] == c[y1] && c[x2] < c[y2])
                            cl++;
                    }
                    cc[p[i]] = cl;
                }
                int[] t = cc;
                cc = c;
                c = t;
            }
            // Kasai
            lcp = new int[n];
            int d = 0;
            for (int i = 0; i < n - 1; i++) {
                d = Math.max(d - 1, 0);
                while (s.charAt(i + d) == s.charAt(p[c[i] - 1] + d))
                    d++;
                lcp[c[i] - 1] = d;
            }
            // Sparse table
            int k = 0;
            while (1 << k <= n) k++;
            mins = new int[k][];
            mins[0] = new int[n - 1];
            for (int i = 0; i < n - 1; i++) {
                mins[0][i] = lcp[i];
            }
            for (int j = 1; j < k; j++) {
                mins[j] = new int[n - (1 << j)];
                for (int i = 0; i < mins[j].length; i++) {
                    mins[j][i] = Math.min(mins[j - 1][i], mins[j - 1][i + (1 << (j - 1))]);
                }
            }
        }

        int lcp(int x, int y) {
            if (x == y) {
                return n - x - 1;
            }
            x = c[x];
            y = c[y];
            if (y < x) {
                int t = x;
                x = y;
                y = t;
            }
            int d = y - x;
            int k = 0;
            while (1 << (k + 1) <= d) k++;
            return Math.min(mins[k][x], mins[k][y - (1 << k)]);
        }

        int[] cnt;
        int[] p;
        int[] pp;
        int[] c;
        int[] cc;
        int[] lcp;
        int[][] mins;

        private void sort() {
            Arrays.fill(cnt, 0);
            for (int i = 0; i < n; i++) {
                cnt[c[i] + 1]++;
            }
            for (int i = 1; i < cnt.length; i++) {
                cnt[i] += cnt[i - 1];
            }
            for (int i = 0; i < n; i++) {
                pp[cnt[c[p[i]]]++] = p[i];
            }
            int[] t = pp;
            pp = p;
            p = t;
        }
    }

    // ------------------

    BufferedReader br;
    PrintWriter out;
    //    BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
    StringTokenizer st;
//    PrintWriter out = new PrintWriter(System.out);

    String next() throws IOException {
        while (st == null || !st.hasMoreTokens()) {
            st = new StringTokenizer(br.readLine());
        }
        return st.nextToken();
    }

    int nextInt() throws IOException {
        return Integer.parseInt(next());
    }

    public static void main(String[] args) throws IOException {
        new longrepeat().run();
    }

    private void run() throws IOException {
        br = new BufferedReader(new FileReader("longrepeat.in"));
        out = new PrintWriter("longrepeat.out");
        solve();
        out.close();
    }

}
