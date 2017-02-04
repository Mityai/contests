import java.io.*;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.InputMismatchException;

public class Main {
    public static void main(String[] args) throws FileNotFoundException {
//        InputStream inputStream = System.in;
//        OutputStream outputStream = System.out;
        InputStream inputStream = new FileInputStream("cooling.in");
        OutputStream outputStream = new FileOutputStream("cooling.out");
        FastScanner in = new FastScanner(inputStream);
        FastPrinter out = new FastPrinter(outputStream);

        Task solver = new Task(in, out);
        solver.solve();

        out.close();
    }
}

class DinicGraph {

    public static class Edge {
        public int from;
        public int to;
        public int flow;
        public int cap;
        public Edge rev;

        public Edge(int from, int to, int flow, int cap) {
            this.from = from;
            this.to = to;
            this.flow = flow;
            this.cap = cap;
        }
    }

    int n;
    public ArrayList<Edge>[] edges;
    int[] cur;
    int[] q;
    public int[] d;
    public int source, target;

    public DinicGraph(int n, int source, int target) {
        this.source = source;
        this.target = target;
        edges = new ArrayList[n];
        this.n = n;
        for (int i = 0; i < edges.length; i++) {
            edges[i] = new ArrayList<>();
        }
        q = new int[n];
        d = new int[n];
        cur = new int[n];
    }

    public Edge addEdge(int from, int to, int cap) {
        Edge e1 = new Edge(from, to, 0, cap);
        Edge e2 = new Edge(to, from, 0, 0);
        e1.rev = e2;
        e2.rev = e1;
        edges[from].add(e1);
        edges[to].add(e2);
        return e1;
    }

    boolean bfs() {
        int head = 0;
        int tail = 1;
        Arrays.fill(d, Integer.MAX_VALUE);
        d[source] = 0;
        q[0] = source;
        while (head < tail) {
            int v = q[head++];
            for (Edge e : edges[v]) {
                if (e.cap - e.flow > 0 && d[e.to] == Integer.MAX_VALUE) {
                    d[e.to] = d[v] + 1;
                    q[tail++] = e.to;
                    if (e.to == target) {
                        return true;
                    }
                }
            }
        }
        return false;
    }

    public int dfs(int v, int cMin) {
        if (v == target) {
            return cMin;
        }
        for (int i = cur[v]; i < edges[v].size(); cur[v] = ++i) {
            Edge e = edges[v].get(i);
            if (d[e.to] != d[v] + 1 || e.cap - e.flow == 0) {
                continue;
            }
            int add = dfs(e.to, Math.min(cMin, e.cap - e.flow));
            if (add == 0) {
                continue;
            }
            e.flow += add;
            e.rev.flow -= add;
            return add;
        }
        return 0;
    }

    public long getMaxFlow() {
        long flow = 0;
        while (bfs()) {
            Arrays.fill(cur, 0);
            while (true) {
                int add = dfs(source, Integer.MAX_VALUE);
                if (add == 0) {
                    break;
                }
                flow += add;
            }
        }
        return flow;
    }

    public boolean isFullSource() {
        for (Edge e : edges[source]) {
            if (e.flow != e.cap) {
                return false;
            }
        }
        return true;
    }
}

class Task {
    FastScanner in;
    FastPrinter out;

    void solve() {
        int n = in.nextInt();
        int m = in.nextInt();

        DinicGraph g = new DinicGraph(n + 2, n, n + 1);

        DinicGraph.Edge[] edgesID = new DinicGraph.Edge[m];
        int[] minFlow = new int[m];
        for (int i = 0; i < m; i++) {
            int u = in.nextInt() - 1;
            int v = in.nextInt() - 1;
            int l = in.nextInt();
            int c = in.nextInt();

            edgesID[i] = g.addEdge(u, v, c - l);
            minFlow[i] = l;
            g.addEdge(g.source, v, l);
            g.addEdge(u, g.target, l);
        }

        g.getMaxFlow();

        if (g.isFullSource()) {
            out.println("YES");
            for (int i = 0; i < m; i++) {
                out.println(edgesID[i].flow + minFlow[i]);
            }
        } else {
            out.println("NO");
        }
    }

    Task(FastScanner in, FastPrinter out) {
        this.in = in;
        this.out = out;
    }
}

class FastScanner extends BufferedReader {

    boolean isEOF;

    public FastScanner(InputStream is) {
        super(new InputStreamReader(is));
    }

    @Override
    public int read() {
        try {
            return super.read();
        } catch (IOException e) {
            throw new InputMismatchException();
        }
    }

    static boolean isWhiteSpace(int c) {
        return c >= 0 && c <= 32;
    }

    public int nextInt() {
        int c = read();
        while (isWhiteSpace(c)) {
            c = read();
        }
        int sgn = 1;
        if (c == '-') {
            sgn = -1;
            c = read();
        }
        int ret = 0;
        while (c >= 0 && !isWhiteSpace(c)) {
            if (c < '0' || c > '9') {
                throw new NumberFormatException("digit expected " + (char) c
                        + " found");
            }
            ret = ret * 10 + c - '0';
            c = read();
        }
        return ret * sgn;
    }
}

class FastPrinter extends PrintWriter {

    public FastPrinter(OutputStream out) {
        super(out);
    }

    public FastPrinter(Writer out) {
        super(out);
    }
}