import java.io.*;
import java.util.*;

public class tram_mb_slow {
    static class Vertex {
        final List<Vertex> adj = new ArrayList<Vertex>();
        final List<Integer> edgeList = new ArrayList<Integer>();
        boolean visited = false;

        void add(Vertex v, int edgeIndex) {
            adj.add(v);
            edgeList.add(edgeIndex);
        }

        boolean dfs(Vertex parent, Vertex dest, boolean[] usedEdges) {
            if (this == dest) {
                return true;
            } else {
                for (int i = 0; i < adj.size(); ++i) {
                    Vertex next = adj.get(i);
                    if (next != parent) {
                        if (next.dfs(this, dest, usedEdges)) {
                            usedEdges[edgeList.get(i)] = true;
                            return true;
                        }
                    }
                }
            }
            return false;
        }
    }

    static void myAssert(String msg, boolean exp) {
        if (!exp) {
            throw new AssertionError(exp);
        }
    }

    public static void main(String[] args) throws IOException {
        Scanner in = new Scanner(System.in);
        int n = in.nextInt();
        Vertex[] vertices = new Vertex[n];
        for (int i = 0; i < n; ++i) {
            vertices[i] = new Vertex();
        }
        for (int i = 1; i < n; ++i) {
            int src = in.nextInt() - 1;
            int trg = in.nextInt() - 1;
            if (src < 0 || n <= src || trg < 0 || n <= trg) {
                throw new AssertionError("Edge " + i + ": out of bounds");
            }
            vertices[src].add(vertices[trg], i - 1);
            vertices[trg].add(vertices[src], i - 1);
        }
        boolean[] usedEdges = new boolean[n - 1];
        int m = in.nextInt();
        for (int i = 0; i < m; ++i) {
            int src = in.nextInt() - 1;
            int trg = in.nextInt() - 1;
            if (src < 0 || n <= src || trg < 0 || n <= trg) {
                throw new AssertionError("Query " + i + ": out of bounds");
            }
            vertices[src].dfs(null, vertices[trg], usedEdges);
        }
        int ans = 0;
        for (boolean used : usedEdges) {
            if (!used) {
                ++ans;
            }
        }

        PrintWriter out = new PrintWriter(System.out);
        out.println(ans);
        out.close();
    }
}
