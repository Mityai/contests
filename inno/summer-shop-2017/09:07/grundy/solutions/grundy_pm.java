import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.util.*;

/**
 * @author Pavel Mavrin
 */
public class grundy_pm {

    private void solve() throws IOException {
        int n = nextInt();
        int m = nextInt();
        init(n, m);
        for (int i = 0; i < m; i++) {
            addEdge(nextInt() - 1, nextInt() - 1);
        }
        for (int i = 0; i < n; i++) {
            if (!z[i]) {
                dfs(i);
            }
        }
        for (int i = 0; i < n; i++) {
            out.println(gr[i]);
        }
    }

    private int nextInt() throws IOException {
        return Integer.parseInt(next());
    }

    void init(int n, int m) {
        this.n = n;
        this.m = m;
        last = 0;
        head = new int[n];
        nx = new int[m];
        dst = new int[m];
        src = new int[m];
        Arrays.fill(head, -1);
        z = new boolean[n];
        gr = new int[n];
        temp = new boolean[n];
    }

    void addEdge(int x, int y) {
        nx[last] = head[x];
        src[last] = x;
        dst[last] = y;
        head[x] = last;
        last++;
    }

    private void dfs(int x) {
        if (z[x]) return;
        z[x] = true;
        int j = head[x];
        int dd = 0;
        while (j >= 0) {
            int y = dst[j];
            dfs(y);
            dd++;
            j = nx[j];
        }
        for (int i = 0; i < dd; i++) {
            temp[i] = false;
        }
        j = head[x];
        while (j >= 0) {
            int y = dst[j];
            temp[gr[y]] = true;
            j = nx[j];
        }
        gr[x] = dd;
        for (int i = 0; i < dd; i++) {
            if (!temp[i]) {
                gr[x] = i;
                break;
            }
        }

    }

    int n, m;
    int[] head;
    int[] nx;
    int[] src;
    int[] dst;
    boolean[] z;
    int last;
    int[] gr;
    boolean[] temp;

    BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
    StringTokenizer st;
    PrintWriter out = new PrintWriter(System.out);

    String next() throws IOException {
        while (st == null || !st.hasMoreTokens()) {
            st = new StringTokenizer(br.readLine());
        }
        return st.nextToken();
    }

    public static void main(String[] args) throws IOException {
        new grundy_pm().run();
    }

    private void run() throws IOException {
        solve();
        out.close();
    }

}
