//	Задача "Трамваи"
//	Девятая индивидуальная Интернет-олимпиада сезона 2009-2010.
//	Автор задачи - Владимир Ульянцев, ulyantsev@rain.ifmo.ru
//	Автор решения - Нияз Нигматуллин, nigmatullin@rain.ifmo.ru
//	Решение с нахождением LCA за O(n)

import java.io.*;
import java.util.*;

public class tram_nn_NM implements Runnable {
	public static void main(String[] args) {
		new tram_nn_NM().run();
	}

	class FastScanner {
		BufferedReader br;
		StringTokenizer st;
		boolean eof;
		String buf;

		public FastScanner(String fileName) throws FileNotFoundException {
			br = new BufferedReader(new FileReader(fileName));
			nextToken();
		}

		public FastScanner(InputStream stream) {
			br = new BufferedReader(new InputStreamReader(stream));
			nextToken();
		}

		String nextToken() {
			while (st == null || !st.hasMoreTokens()) {
				try {
					st = new StringTokenizer(br.readLine());
				} catch (Exception e) {
					eof = true;
					break;
				}
			}
			String ret = buf;
			buf = eof ? "-1" : st.nextToken();
			return ret;
		}

		int nextInt() {
			return Integer.parseInt(nextToken());
		}

		long nextLong() {
			return Long.parseLong(nextToken());
		}

		double nextDouble() {
			return Double.parseDouble(nextToken());
		}

		void close() {
			try {
				br.close();
			} catch (Exception e) {

			}
		}

		boolean isEOF() {
			return eof;
		}
	}

	FastScanner sc;
	PrintWriter out;

	private static final String FN = "tram";

	public void run() {
		Locale.setDefault(Locale.US);
		try {
			sc = new FastScanner(System.in);
			out = new PrintWriter(System.out);
			solve();
			sc.close();
			out.close();
		} catch (Throwable e) {
			e.printStackTrace();
			System.exit(1);
		}
	}

	void doAssert(boolean isRight, String s) {
		if (!isRight)
			throw new AssertionError(s);
	}

	class Edge {
		int to;
		boolean ok;

		public Edge(int to) {
			this.to = to;
			ok = true;
		}

	}

	ArrayList<Edge>[] edges;
	int[][] dp;
	int[] parent, level, lca, begin;
	int n, ans;
	Edge[] edge;
	boolean[] was;

	int dfs2(int x) {
		int ret = begin[x];
		for (Edge e : edges[x]) {
			int i = e.to;
			if (i == parent[x]) {
				continue;
			}
			int got = dfs2(i);
			if (got == 0) {
				++ans;
			}
			ret += got;
		}
		return ret - 2 * lca[x];
	}

	void mark(int x, int y) {
		if (level[x] > level[y]) {
			int tmp = x;
			x = y;
			y = tmp;
		}
		while (level[y] > level[x]) {
			edge[y].ok = false;
			y = parent[y];
		}
		while (x != y) {
			edge[x].ok = false;
			edge[y].ok = false;
			x = parent[x];
			y = parent[y];
		}
	}

	void dfs1(int x, int parent, int level, Edge r) {
		doAssert(this.parent[x] == -2, "it's not a tree");
		this.parent[x] = parent;
		this.level[x] = level;
		this.edge[x] = r;
		for (Edge e : edges[x]) {
			int i = e.to;
			if (i == parent) {
				continue;
			}
			dfs1(i, x, level + 1, e);
		}
	}

	private void solve() {
		n = sc.nextInt();
		doAssert(2 <= n && n <= 100000, "n is out of bounds");
		edges = new ArrayList[n];
		parent = new int[n];
		was = new boolean[n];
		edge = new Edge[n];
		level = new int[n];
		Arrays.fill(parent, -2);
		for (int i = 0; i < n; i++) {
			edges[i] = new ArrayList<Edge>();
		}
		for (int i = 0; i < n - 1; i++) {
			int x = sc.nextInt() - 1;
			int y = sc.nextInt() - 1;
			doAssert(0 <= x && x < n && 0 <= y && y < n && x != y,
					"invalid edge: line " + (i + 2));
			edges[x].add(new Edge(y));
			edges[y].add(new Edge(x));
		}
		dfs1(0, -1, 0, null);
		for (int i = 0; i < n; i++) {
			doAssert(parent[i] != -2, "it's not a tree");
		}
		int m = sc.nextInt();
		doAssert(0 <= m && m <= 100000, "m is out of bounds");
		for (int i = 0; i < m; i++) {
			int x = sc.nextInt() - 1;
			int y = sc.nextInt() - 1;
			doAssert(0 <= x && x < n && 0 <= y && y < n && x != y,
					"invalid number of vertices: line " + (i + n + 3));
			mark(x, y);
		}
		ans = 0;
		for (int i = 0; i < n; i++) {
			for (Edge e : edges[i]) {
				if (e.to == parent[i]) {
					continue;
				}
				if (e.ok) {
					ans++;
				}
			}
		}
		out.println(ans);
	}
}
