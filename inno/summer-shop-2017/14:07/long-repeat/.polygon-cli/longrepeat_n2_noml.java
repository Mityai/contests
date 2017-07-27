import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.StringTokenizer;

/**
 * @author Pavel Mavrin
 */
public class longrepeat_n2_noml {

    private void solve() throws IOException {
        String s = next();
        int n = s.length();
        int res = 1;
        for (int d = 1; d < n; d++) {
            int c = 0;
            for (int i = n - 1 - d; i >= 0; i--) {
                int j = i + d;
                if (s.charAt(i) == s.charAt(j)) {
                    c++;
                    res = Math.max(res, (c + d) / d);
                } else {
                    c = 0;
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
        new longrepeat_n2_noml().run();
    }

    private void run() throws IOException {
        br = new BufferedReader(new FileReader("longrepeat.in"));
        out = new PrintWriter("longrepeat.out");
        solve();
        out.close();
    }

}
