import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Arrays;
import java.util.StringTokenizer;

/**
 * @author Pavel Mavrin
 */
public class longrepeat_n2 {

    private void solve() throws IOException {
        String s = next();
        int n = s.length();
        int[][] lcp = new int[n][n];
        int res = 1;
        for (int i = n - 1; i >= 0; i--) {
            for (int j = n - 1; j > i; j--) {
                if (s.charAt(i) == s.charAt(j)) {
                    if (j == n - 1) {
                        lcp[i][j] = 1;
                    } else {
                        lcp[i][j] = 1 + lcp[i + 1][j + 1];
                    }
                    int d = j - i;
                    res = Math.max(res, (lcp[i][j] + d) / d);
                }
            }
        }
        out.println(res);
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
        new longrepeat_n2().run();
    }

    private void run() throws IOException {
        br = new BufferedReader(new FileReader("longrepeat.in"));
        out = new PrintWriter("longrepeat.out");
        solve();
        out.close();
    }

}
