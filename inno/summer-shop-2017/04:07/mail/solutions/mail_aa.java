import java.io.*;
import java.util.*;
import java.math.*;

public class mail_aa {
	public static void main(String[] args) {
		new mail_aa().run();
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
		c = new int[n];
		heavy = new int[n];
		p = new int[n];
		Arrays.fill(heavy, -1);
		dfs(0, 0, 0);
		int[][] d = new int[20][n];
		for (int i = 0; i < d[0].length; i++) {
			d[0][i] = p[i];
		}
		for (int i = 0; i + 1 < d.length; i++) {
			for (int j = 0; j < d[i + 1].length; j++) {
				d[i + 1][j] = d[i][d[i][j]];
			}
		}
		Arrays.fill(u, false);
		pos = new int[n];
		tree = new Tree[n];
		createsTrees(0, 0);
		int m = inBounds(nextInt(), 1, BOUND, "k");
		for (int i = 0; i < m; i++) {
			char c = nextToken().charAt(0);
			int s = inBounds(nextInt(), 1, n, "i_" + (i + 1)) - 1;
			if (c == '!') {
				a[s] = inBounds(nextInt(), 1, BOUND, "v_" + (i + 1));
				tree[s].set(pos[s], a[s]);
			} else if (c == '?') {
				int t = inBounds(nextInt(), 1, n, "j_" + (i + 1)) - 1;
				int x = s;
				int y = t;
				for (int j = d.length - 1; j >= 0; j--) {
					if (h[x] > h[y] && d[j][x] >= 0 && h[d[j][x]] >= h[y]) {
						x = d[j][x];
					}
					if (h[x] < h[y] && d[j][y] >= 0 && h[d[j][y]] >= h[x]) {
						y = d[j][y];
					}
				}
				for (int j = d.length - 1; j >= 0; j--) {
					if (x == y) {
						break;
					}
					if (d[j][x] != d[j][y]) {
						x = d[j][x];
						y = d[j][y];
					}
				}
				if (x != y) {
					x = p[x];
					y = p[y];
				}
				if (x != y) {
					throw new Error("Something strange");
				}
				int ans = 0;
				while (tree[s].id != tree[x].id) {
					ans = Math.max(ans, tree[s].get(0, pos[s]));
					s = tree[s].p;
				}
				ans = Math.max(ans, tree[s].get(pos[x], pos[s]));
				while (tree[t].id != tree[x].id) {
					ans = Math.max(ans, tree[t].get(0, pos[t]));
					t = tree[t].p;
				}
				ans = Math.max(ans, tree[t].get(pos[x], pos[t]));
				out.println(ans);
			} else {
				throw new Error("Wrong character in request " + (i + 1) + ": "
						+ c);
			}
		}
	}

	int id = 0;

	private void createsTrees(int x, int sz) {
		u[x] = true;
		if (heavy[x] >= 0) {
			createsTrees(heavy[x], sz + 1);
			tree[x] = tree[heavy[x]];
		} else {
			tree[x] = new Tree(sz + 1, id++);
		}
		pos[x] = sz;
		tree[x].set(pos[x], a[x]);
		if (sz == 0) {
			tree[x].p = p[x];
		}
		for (int i : g[x]) {
			if (!u[i]) {
				createsTrees(i, 0);
			}
		}
	}

	Tree[] tree;
	int[] pos;

	private void dfs(int x, int y, int j) {
		p[x] = j;
		h[x] = y;
		u[x] = true;
		c[x] = 1;
		int max = -1;
		int maxi = -1;
		for (int i : g[x]) {
			if (!u[i]) {
				dfs(i, y + 1, x);
				c[x] += c[i];
				if (max < c[i]) {
					max = c[i];
					maxi = i;
				}
			}
		}
		if (maxi >= 0) {
			heavy[x] = maxi;
		}
	}

	ArrayList<Integer>[] g;
	int[] a;
	int[] h;
	int[] c;
	int[] p;
	boolean[] u;
	int[] heavy;

	class Tree {
		int[] q;
		int m;
		int id;
		int p;

		public Tree(int n, int id) {
			this.id = id;
			m = 1;
			while (m < n) {
				m <<= 1;
			}
			q = new int[2 * m];
		}

		public int get(int i, int j) {
			i += m;
			j += m;
			int ans = 0;
			while (i <= j) {
				if (i % 2 == 1) {
					ans = Math.max(ans, q[i]);
				}
				if (j % 2 == 0) {
					ans = Math.max(ans, q[j]);
				}
				i = (i + 1) / 2;
				j = (j - 1) / 2;
			}
			return ans;
		}

		public void set(int i, int j) {
			i += m;
			q[i] = j;
			while (i > 1) {
				i /= 2;
				q[i] = Math.max(q[2 * i], q[2 * i + 1]);
			}
		}
	}
}
