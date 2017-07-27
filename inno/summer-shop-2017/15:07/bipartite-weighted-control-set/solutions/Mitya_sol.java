import java.io.*;
import java.util.ArrayList;
import java.util.List;
import java.util.StringTokenizer;

public class Mitya_sol {

    void solve() throws IOException {
        int n = in.nextInt();
        int m = in.nextInt();
        int[] a = new int[n];
        for (int i = 0; i < n; i++) {
            a[i] = in.nextInt();
        }
        int[] b = new int[n];
        for (int i = 0; i < n; i++) {
            b[i] = in.nextInt();
        }
        List<Integer>[] edges = new ArrayList[n + n];
        for (int i = 0; i < edges.length; i++) {
            edges[i] = new ArrayList<>();
        }
        for (int i = 0; i < m; i++) {
            int from = in.nextInt() - 1;
            int to = in.nextInt() - 1 + n;
            edges[from].add(to);
            edges[to].add(from);
        }
        boolean[] used = new boolean[n + n];
        int[] queue = new int[n + n];
        int ans = 0;
        for (int i = 0; i < n; i++) {
            if (!used[i]) {
                List<Integer> component = new ArrayList<>();
                int head = 0;
                int tail = 0;
                queue[tail++] = i;
                used[i] = true;
                component.add(i);
                while (head < tail) {
                    int v = queue[head++];
                    for (int to : edges[v]) {
                        if (!used[to]) {
                            component.add(to);
                            used[to] = true;
                            queue[tail++] = to;
                        }
                    }
                }
                int sumA = 0;
                int sumB = 0;
                for (int v : component) {
                    if (v < n) {
                        sumA += a[v];
                    } else {
                        sumB += b[v - n];
                    }
                }
                ans += Math.min(sumA, sumB);
            }
        }
        out.println(ans);
    }

    static TaskBReader in;
    static PrintWriter out;
    static PrintStream err;

    public static void main(String[] args) {
        try {
            in = new TaskBReader();
            out = new PrintWriter(System.out);
            err = System.err;
            new Mitya_sol().solve();
            out.close();
        } catch (Exception e) {
            e.printStackTrace();
            System.exit(1);
        }
    }
}

class TaskBReader extends BufferedReader {
    StringTokenizer st;

    TaskBReader(InputStream is) {
        super(new InputStreamReader(is));
    }

    TaskBReader() {
        this(System.in);
    }

    TaskBReader(String file) throws FileNotFoundException {
        this(new FileInputStream(file));
    }

    String nextToken() throws IOException {
        while (st == null || !st.hasMoreElements()) {
            st = new StringTokenizer(readLine());
        }
        return st.nextToken();
    }

    public boolean hasMoreTokens() throws IOException {
        if (st != null && st.hasMoreTokens()) {
            return true;
        }
        String line = readLine();
        if (line == null) {
            return false;
        }
        st = new StringTokenizer(line);
        return true;
    }

    int nextInt() throws IOException {
        return Integer.parseInt(nextToken());
    }

    long nextLong() throws IOException {
        return Long.parseLong(nextToken());
    }

    double nextDouble() throws IOException {
        return Double.parseDouble(nextToken());
    }
}