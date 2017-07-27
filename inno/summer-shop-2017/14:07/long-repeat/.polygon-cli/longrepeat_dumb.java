import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Arrays;
import java.util.StringTokenizer;

/**
 * @author Pavel Mavrin
 */
public class longrepeat_dumb {

    private void solve() throws IOException {
        String s = next();
        int n = s.length();
        int res = 1;
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j <= n; j++) {
                String t = s.substring(i, j);
                int q = 1;
                int k = j;
                while (k + (j - i) <= n && s.substring(k, k + j - i).equals(t)) {
                    q++;
                    k += j - i;
                }
                res = Math.max(res, q);
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
        new longrepeat_dumb().run();
    }

    private void run() throws IOException {
        br = new BufferedReader(new FileReader("longrepeat.in"));
        out = new PrintWriter("longrepeat.out");
        solve();
        out.close();
    }

}
