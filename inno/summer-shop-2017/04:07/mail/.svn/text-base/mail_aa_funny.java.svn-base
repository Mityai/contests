import java.io.*;
import java.util.*;
import java.math.*;

public class mail_aa_funny {
	public static void main(String[] args) {
		new mail_aa_funny().run();
	}

	BufferedReader br;
	StringTokenizer st;
	PrintWriter out;
	boolean eof = false;

	public void run() {
		Locale.setDefault(Locale.US);
		try {
			br = new BufferedReader(new FileReader(FNAME + ".in"));
			out = new PrintWriter(FNAME + ".out");
			solve();
			out.close();
		} catch (Throwable e) {
			e.printStackTrace();
			System.exit(566);
		}
	}

	String nextToken() {
		while (st == null || !st.hasMoreTokens()) {
			try {
				st = new StringTokenizer(br.readLine());
			} catch (Exception e) {
				eof = true;
				return "0";
			}
		}
		return st.nextToken();
	}

	int nextInt() {
		return Integer.parseInt(nextToken());
	}

	void myAssert(boolean u, String message) {
		if (!u) {
			throw new Error("Assertion failed!!! " + message);
		}
	}

	int inBounds(int x, int l, int r, String name) {
		myAssert(l <= x && x <= r, name + " is not in bounds: " + x
				+ " not in [" + l + ", " + r + "]");
		return x;
	}

	String FNAME = "mail";

	int BOUND = (int) 1e5;

	private void solve() throws IOException {
		int n = inBounds(nextInt(), 1, BOUND / 2, "n");
		a = new int[n];
		for (int i = 0; i < a.length; i++) {
			a[i] = inBounds(nextInt(), 1, BOUND, "h_" + (i + 1));
		}
		g = new ArrayList[n];
		for (int i = 0; i < g.length; i++) {
			g[i] = new ArrayList<Integer>();
		}
		for (int i = 0; i < n - 1; i++) {
			int x = inBounds(nextInt(), 1, n, "u_" + (i + 1)) - 1;
			int y = inBounds(nextInt(), 1, n, "v_" + (i + 1)) - 1;
			g[x].add(y);
			g[y].add(x);
		}
		h = new int[n];
		u = new boolean[n];
		p = new int[n];
		dfs(0, 0, 0);
		d = new int[20][n];
		max = new int[d.length][n];
		for (int i = 0; i < d[0].length; i++) {
			d[0][i] = p[i];
			max[0][i] = Math.max(a[i], a[p[i]]);
		}
		for (int i = 0; i + 1 < d.length; i++) {
			for (int j = 0; j < d[i + 1].length; j++) {
				d[i + 1][j] = d[i][d[i][j]];
				max[i + 1][j] = Math.max(max[i][j], max[i][d[i][j]]);
			}
		}
		int m = inBounds(nextInt(), 1, BOUND, "k");
		for (int step = 0; step < m; step++) {
			String str = nextToken();
			myAssert(str.length() == 1, "strange string: " + str);
			char c = str.charAt(0);
			myAssert(c == '!' || c == '?', "strange string: " + c);
			int i = inBounds(nextInt(), 1, n, "i_" + (step + 1)) - 1;
			if (c == '!') {
				int v = inBounds(nextInt(), 1, BOUND, "v_" + (step + 1));
				a[i] = v;
				ArrayList<Integer> subTree = new ArrayList<Integer>();
				getSubTree(i, subTree);
				for (int j : subTree) {
					max[0][j] = Math.max(a[j], a[p[j]]);
				}
				for (int k = 0; k + 1 < max.length; k++) {
					for (int j : subTree) {
						max[k + 1][j] = Math.max(max[k][j], max[k][d[k][j]]);
					}
				}
			} else {
				int j = inBounds(nextInt(), 1, n, "i_" + (step + 1)) - 1;
				ans = Math.max(a[i], a[j]);
				lca(i, j);
				out.println(ans);
			}
		}
	}

	private int lca(int x, int y) {
		x = adjustHeight(x, h[y]);
		y = adjustHeight(y, h[x]);
		for (int i = d.length - 1; i >= 0; i--) {
			if (d[i][x] != d[i][y]) {
				ans = Math.max(ans, max[i][x]);
				ans = Math.max(ans, max[i][y]);
				x = d[i][x];
				y = d[i][y];
			}
		}
		if (x != y) {
			x = p[x];
			y = p[y];
		}
		ans = Math.max(ans, a[x]);
		return ans;
	}

	private int adjustHeight(int x, int height) {
		for (int i = d.length - 1; i >= 0; i--) {
			if (h[d[i][x]] >= height) {
				ans = Math.max(ans, max[i][x]);
				x = d[i][x];
			}
		}
		return x;
	}

	private void getSubTree(int x, ArrayList<Integer> subTree) {
		subTree.add(x);
		for (int i : g[x]) {
			if (i != p[x]) {
				getSubTree(i, subTree);
			}
		}
	}

	private void dfs(int x, int y, int z) {
		h[x] = z;
		p[x] = y;
		u[x] = true;
		for (int i : g[x]) {
			if (!u[i]) {
				dfs(i, x, z + 1);
			}
		}
	}

	int ans;
	ArrayList<Integer>[] g;
	int[] h;
	boolean[] u;
	int[] p;
	int[] a;
	int[][] d;
	int[][] max;
}