import java.io.*;
import java.util.*;
import java.math.*;

public class mail_aa_lct {
	public static void main(String[] args) {
		new mail_aa_lct().run();
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
		int n = inBounds(nextInt(), 1, BOUND, "n");
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
		v = new Vertex[n];
		h = new int[n];
		parent = new int[n];
		dfs(0, 0, 0);
		d = new int[30][n];
		for (int i = 0; i < d[0].length; i++) {
			d[0][i] = parent[i];
		}
		for (int i = 0; i + 1 < d.length; i++) {
			for (int j = 0; j < d[i + 1].length; j++) {
				d[i + 1][j] = d[i][d[i][j]];
			}
		}
		parent[0] = -1;
		int m = inBounds(nextInt(), 1, BOUND, "k");
		for (int req = 0; req < m; req++) {
			String tmp = nextToken();
			myAssert(tmp.length() == 1, "Stange string: " + tmp);
			char c = tmp.charAt(0);
			myAssert(c == '!' || c == '?', "Stange string: " + c);
			int i = inBounds(nextInt(), 1, n, "i_" + (req + 1)) - 1;
			if (c == '!') {
				int val = inBounds(nextInt(), 1, BOUND, "v");
				cut(v[i]);
				v[i].val = val;
				if (parent[i] != -1) {
					link(v[i], v[parent[i]]);
				}
			} else {
				int j = inBounds(nextInt(), 1, n, "j_" + (req + 1)) - 1;
				int x = lca(i, j);
				cut(v[x]);
				int ans = 0;
				ans = Math.max(ans, getMax(v[i]));
				ans = Math.max(ans, getMax(v[j]));
				out.println(ans);
				if (parent[x] != -1) {
					link(v[x], v[parent[x]]);
				}
			}
		}
	}

	private int getMax(Vertex v) {
		expose(v);
		return v.getPath().root.max;
	}

	private int lca(int x, int y) {
		for (int i = d.length - 1; i >= 0; i--) {
			if (h[d[i][x]] >= h[y]) {
				x = d[i][x];
			}
			if (h[d[i][y]] >= h[x]) {
				y = d[i][y];
			}
		}
		myAssert(h[x] == h[y], "something wrong in lca");
		for (int i = d.length - 1; i >= 0; i--) {
			if (d[i][x] != d[i][y]) {
				x = d[i][x];
				y = d[i][y];
			}
		}
		if (x != y) {
			x = parent[x];
			y = parent[y];
		}
		myAssert(x == y, "something wrong in lca2");
		return x;
	}

	int[][] d;

	private void dfs(int x, int height, int p) {
		parent[x] = p;
		v[x] = new Vertex(x, a[x]);
		if (p != x) {
			v[x].path.successor = v[p];
		}
		h[x] = height;
		for (int i : g[x]) {
			if (v[i] == null) {
				dfs(i, height + 1, x);
			}
		}
	}

	int[] parent;
	Vertex[] v;
	int[] h;

	Path link(Vertex v, Vertex w) {
		expose(v);
		return join(null, v, expose(w));
	}

	int[] a;
	ArrayList<Integer>[] g;

	class Path {
		public Path(Vertex r, Vertex s) {
			if (r == null) {
				return;
			}
			root = r;
			r.p = null;
			root.path = this;
			successor = s;
		}

		@Override
		public String toString() {
			return (successor == null ? "x" : successor.n + 1 + "") + " ("
					+ root + ")";
		}

		Vertex root;
		Vertex successor;
	}

	void cut(Vertex v) {
		expose(v);
		splay(v);
		v.r = null;
		new Path(v, null);
	}

	Path expose(Vertex v) {
		Path p = null;
		while (v != null) {
			Vertex w = v.getPath().successor;
			split(v);
			new Path(sleft, v);
			Path r = new Path(sright, null);
			p = join(p, v, r);
			v = w;
		}
		return p;
	}

	private Path join(Path p, Vertex v, Path r) {
		Vertex vl = p == null ? null : p.root;
		if (vl != null) {
			while (vl.r != null) {
				vl = vl.r;
			}
			vl = splay(vl);
		}
		Vertex vr = r == null ? null : r.root;
		if (vr != null) {
			while (vr.l != null) {
				vr = vr.l;
			}
			vr = splay(vr);
		}
		v.l = vl;
		v.r = vr;
		v.norm();
		return new Path(v, r == null ? null : r.successor);
	}

	private void split(Vertex v) {
		splay(v);
		sleft = v.l;
		sright = v.r;
		v.l = null;
		v.r = null;
	}

	Vertex sleft, sright;

	class Vertex {
		Vertex p, l, r;
		Path path;
		int n;
		int val;
		int max;

		@Override
		public String toString() {
			String s = "";
			if (l != null) {
				s += "[" + l + "] ";
			}
			s += n + 1;
			if (r != null) {
				s += " [" + r + "]";
			}
			return s;
		}

		public Vertex(int x, int i) {
			n = x;
			val = i;
			path = new Path(this, null);
		}

		public Path getPath() {
			return p == null ? path : p.getPath();
		}

		public void norm() {
			max = val;
			if (l != null) {
				l.p = this;
				max = Math.max(max, l.max);
			}
			if (r != null) {
				r.p = this;
				max = Math.max(max, r.max);
			}
		}
	}

	Vertex rotate(Vertex x) {
		Vertex p = x.p;
		if (p == null) {
			return x;
		}
		Vertex g = p.p;
		if (g == null) {
			if (p.l == x) {
				p.l = x.r;
				x.r = p;
			} else {
				p.r = x.l;
				x.l = p;
			}
			p.norm();
			x.norm();
			return x;
		}
		if (p.l == x) {
			if (g.l == p) {
				p.l = x.r;
				x.r = p;
				g.l = p.r;
				p.r = g;
			} else {
				g.r = x.l;
				x.l = g;
				p.l = x.r;
				x.r = p;
			}
		} else {
			if (g.l == p) {
				p.r = x.l;
				x.l = p;
				g.l = x.r;
				x.r = g;
			} else {
				p.r = x.l;
				x.l = p;
				g.r = p.l;
				p.l = g;
			}
		}
		g.norm();
		p.norm();
		x.norm();
		return x;
	}

	Vertex splay(Vertex x) {
		Path path = x.getPath();
		while (x.p != null) {
			Vertex p = x.p;
			Vertex g = p.p;
			Vertex gg = null;
			boolean left = false;
			if (g != null) {
				gg = g.p;
				left = gg == null || gg.l == g;
			}
			x = rotate(x);
			if (gg != null) {
				if (left) {
					gg.l = x;
				} else {
					gg.r = x;
				}
				gg.norm();
			} else {
				x.p = null;
			}
		}
		path.root = x;
		x.path = path;
		return x;
	}

}
