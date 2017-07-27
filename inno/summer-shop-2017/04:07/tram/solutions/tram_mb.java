import java.io.*;
import java.util.*;

public class tram_mb {
    static class Vertex {
        final List<Vertex> adj = new ArrayList<Vertex>();
        final List<Vertex> queries = new ArrayList<Vertex>();

        Vertex parent = this;
        Vertex ancestor = this;
        int rank = 0;
        final int index;

        boolean visited = false;
        int depth = -1;
        int uplink = 0;

        Vertex(int index) {
            this.index = index;
        }

        Vertex parent() {
            if (this == parent) {
                return this;
            } else {
                return parent = parent.parent();
            }
        }

        void uniteDown(Vertex v) {
            Vertex refThis = parent();
            Vertex refThat = v.parent();
            if (refThis != refThat) {
                if (refThis.rank != refThat.rank) {
                    ++refThis.rank;
                }
                if (refThis.rank > refThat.rank) {
                    refThat.parent = refThis;
                } else {
                    refThis.parent = refThat;
                }
            }
            parent().ancestor = this;
        }
    }

    static void dfs1(Vertex vertex, Vertex parent) {
        if (vertex.visited) {
            throw new AssertionError("Graph contains cycles");
        }
        for (Vertex v : vertex.adj) {
            if (v != parent) {
                v.depth = vertex.depth + 1;
                dfs1(v, vertex);
                vertex.uniteDown(v);
            }
        }
        vertex.visited = true;
        for (Vertex v : vertex.queries) {
            if (v.visited) {
                Vertex ancestor = v.parent().ancestor;
                vertex.uplink = Math.max(vertex.uplink, vertex.depth - ancestor.depth);
                v.uplink = Math.max(v.uplink, v.depth - ancestor.depth);
            }
        }
    }

    static int dfs2(Vertex vertex, Vertex parent) {
        int rv = 0;
        for (Vertex v : vertex.adj) {
            if (v != parent) {
                rv += dfs2(v, vertex);
                vertex.uplink = Math.max(vertex.uplink, v.uplink - 1);
            }
        }
        rv += vertex.uplink > 0 ? 1 : 0;
        return rv;
    }

    static void myAssert(String msg, boolean exp) {
        if (!exp) {
            throw new AssertionError(exp);
        }
    }

    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));;
        int n = Integer.parseInt(in.readLine());
        Vertex[] vertices = new Vertex[n];
        for (int i = 0; i < n; ++i) {
            vertices[i] = new Vertex(i);
        }
        for (int i = 1; i < n; ++i) {
            String line = in.readLine();
            int ws = line.indexOf(' ');
            if (ws == -1) {
                throw new AssertionError("Edge " + i + ": wrong input format");
            }
            int src = Integer.parseInt(line.substring(0, ws)) - 1;
            int trg = Integer.parseInt(line.substring(ws + 1)) - 1;
            if (src < 0 || n <= src || trg < 0 || n <= trg) {
                throw new AssertionError("Edge " + i + ": out of bounds");
            }
            vertices[src].adj.add(vertices[trg]);
            vertices[trg].adj.add(vertices[src]);
        }
        int m = Integer.parseInt(in.readLine());
        for (int i = 0; i < m; ++i) {
            String line = in.readLine();
            int ws = line.indexOf(' ');
            if (ws == -1) {
                throw new AssertionError("Query " + (i + 1) + ": wrong input format");
            }
            int src = Integer.parseInt(line.substring(0, ws)) - 1;
            int trg = Integer.parseInt(line.substring(ws + 1)) - 1;
            if (src < 0 || n <= src || trg < 0 || n <= trg) {
                throw new AssertionError("Query " + (i + 1) + ": out of bounds");
            }
            vertices[src].queries.add(vertices[trg]);
            vertices[trg].queries.add(vertices[src]);
        }

        vertices[0].depth = 0;
        dfs1(vertices[0], null);

        for (Vertex v : vertices) {
            if (!v.visited) {
                throw new AssertionError("Graph is not connected");
            }
        }

        int ans = dfs2(vertices[0], null);

        PrintWriter out = new PrintWriter(System.out);
        out.println(n - 1 - ans);
        out.close();
    }
}
