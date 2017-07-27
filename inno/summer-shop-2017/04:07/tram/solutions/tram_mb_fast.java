import java.io.*;
import java.util.*;

public class tram_mb_fast {
    static int[] adjc;
    static int[][] adj;

    static int[] qc;
    static int[][] q;

    static int[] p, r, a;
    static boolean[] used;
    static int[] depth;
    static int[] uplink;

    static int dsGet(int idx) {
        return p[idx] == idx ? idx : (p[idx] = dsGet(p[idx]));
    }

    static void dsUnite(int major, int minor) {
        int anc = major;
        major = dsGet(major);
        minor = dsGet(minor);
        if (major != minor) {
            if (r[major] == r[minor]) {
                ++r[major];
            }
            if (r[major] > r[minor]) {
                p[minor] = major;
            } else {
                p[major] = minor;
            }
        }
        a[dsGet(major)] = anc;
    }

    static void dfs1(int vertex, int parent) {
        for (int v : adj[vertex]) {
            if (v != parent) {
                depth[v] = depth[vertex] + 1;
                dfs1(v, vertex);
                dsUnite(vertex, v);
            }
        }
        used[vertex] = true;
        for (int v : q[vertex]) {
            if (used[v]) {
                int ancestor = a[dsGet(v)];
                uplink[vertex] = Math.max(uplink[vertex], depth[vertex] - depth[ancestor]);
                uplink[v] = Math.max(uplink[v], depth[v] - depth[ancestor]);
            }
        }
    }

    static int dfs2(int vertex, int parent) {
        int rv = 0;
        for (int v : adj[vertex]) {
            if (v != parent) {
                rv += dfs2(v, vertex);
                uplink[vertex] = Math.max(uplink[vertex], uplink[v] - 1);
            }
        }
        rv += uplink[vertex] > 0 ? 1 : 0;
        return rv;
    }

    static void myAssert(String msg, boolean exp) {
        if (!exp) {
            throw new AssertionError(exp);
        }
    }

    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        int n = Integer.parseInt(in.readLine());

        adjc = new int[n];
        adj = new int[n][];
        qc = new int[n];
        q = new int[n][];
        p = new int[n];
        r = new int[n];
        a = new int[n];
        for (int i = 0; i < n; ++i) {
            p[i] = i;
            a[i] = i;
        }
        used = new boolean[n];
        depth = new int[n];
        uplink = new int[n];

        int[] edgeStart = new int[n - 1];
        int[] edgeFinish = new int[n - 1];

        for (int i = 0; i < n - 1; ++i) {
            String line = in.readLine();
            int ws = line.indexOf(' ');
            int src = Integer.parseInt(line.substring(0, ws)) - 1;
            int trg = Integer.parseInt(line.substring(ws + 1)) - 1;
            ++adjc[src];
            ++adjc[trg];
            edgeStart[i] = src;
            edgeFinish[i] = trg;
        }
        for (int i = 0; i < n; ++i) {
            adj[i] = new int[adjc[i]];
            adjc[i] = 0;
        }
        for (int i = 0; i < n - 1; ++i) {
            int es = edgeStart[i];
            int ef = edgeFinish[i];
            adj[es][adjc[es]++] = ef;
            adj[ef][adjc[ef]++] = es;
        }

        int m = Integer.parseInt(in.readLine());
        int[] qStart = new int[m];
        int[] qFinish = new int[m];
        for (int i = 0; i < m; ++i) {
            String line = in.readLine();
            int ws = line.indexOf(' ');
            int src = Integer.parseInt(line.substring(0, ws)) - 1;
            int trg = Integer.parseInt(line.substring(ws + 1)) - 1;
            qStart[i] = src;
            qFinish[i] = trg;
            qc[src]++;
            qc[trg]++;
        }
        for (int i = 0; i < n; ++i) {
            q[i] = new int[qc[i]];
            qc[i] = 0;
        }
        for (int i = 0; i < m; ++i) {
            int es = qStart[i];
            int ef = qFinish[i];
            q[es][qc[es]++] = ef;
            q[ef][qc[ef]++] = es;
        }

        dfs1(0, -1);

        int ans = dfs2(0, -1);

        PrintWriter out = new PrintWriter(System.out);
        out.println(n - 1 - ans);
        out.close();
    }
}
