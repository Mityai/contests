import java.io.*;
import java.util.*;
import java.math.*;

public class mail_aa_extra_splay_tl {
	public static void main(String[] args) {
		new mail_aa_extra_splay_tl().run();
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
		int n = nextInt();
		v = new Vertex[n];
		g = new ArrayList[n];
		for (int i = 0; i < v.length; i++) {
			v[i] = new Vertex(i, nextInt());
			v[i].t = new Tree(v[i]);
			v[i].t.path = new Path(v[i].t, null);
			g[i] = new ArrayList<Integer>();
		}
		for (int i = 0; i < n - 1; i++) {
			int x = nextInt() - 1;
			int y = nextInt() - 1;
			g[x].add(y);
			g[y].add(x);
		}
		dfs(0, 0, null);
		Vertex[][] d = new Vertex[20][n];
		for (int i = 0; i < d[0].length; i++) {
			d[0][i] = v[i].parent;
		}
		for (int i = 0; i + 1 < d.length; i++) {
			for (int j = 0; j < d[i].length; j++) {
				d[i + 1][j] = d[i][j] == null ? null : d[i][d[i][j].n];
			}
		}
		int m = nextInt();
		for (int req = 0; req < m; req++) {
			if (req % 1000 == 0) {
				System.out.println(req);
			}
			char c = nextToken().charAt(0);
			int i = nextInt() - 1;
			if (c == '!') {
				int val = nextInt();
				Path p = expose(v[i]);
				p.split(v[i]);
				paths[1].root.setValue(val);
			} else {
				int j = nextInt() - 1;
				int x = getLCA(d, i, j);
				Path p = expose(v[x]);
				p.split(v[x]);
				paths[1].successor = null;
				int ans = 0;
				ans = Math.max(ans, expose(v[i]).root.max);
				ans = Math.max(ans, expose(v[j]).root.max);
				out.println(ans);
				Path y = expose(v[x]);
				y.successor = v[x].parent;
			}
		}
	}

	private void debug() {
		System.out.println("debug");
		for (int i = 0; i < v.length; i++) {
			System.out.println(getPath(v[i]));
		}
	}

	Path[] paths = new Path[3];
	Tree[] split = new Tree[2];

	private int getLCA(Vertex[][] d, int x, int y) {
		for (int i = d.length - 1; i >= 0; i--) {
			if (d[i][x] != null && d[i][x].h >= v[y].h) {
				x = d[i][x].n;
			}
			if (d[i][y] != null && d[i][y].h >= v[x].h) {
				y = d[i][y].n;
			}
		}
		for (int i = d.length - 1; i >= 0; i--) {
			if (d[i][x] != d[i][y]) {
				x = d[i][x].n;
				y = d[i][y].n;
			}
		}
		if (x != y) {
			x = v[x].parent.n;
			y = v[y].parent.n;
		}
		return x;
	}

	private void dfs(int x, int h, Vertex p) {
		v[x].parent = p;
		v[x].u = true;
		v[x].h = h++;
		v[x].t.path.successor = p;
		for (int i : g[x]) {
			if (!v[i].u) {
				dfs(i, h, v[x]);
			}
		}
	}

	Vertex[] v;
	ArrayList<Integer>[] g;

	class Path {
		Tree root;
		Vertex successor;

		@Override
		public String toString() {
			return successor + " [" + root + "]";
		}

		public Path(Tree t, Vertex v) {
			root = t;
			root.path = this;
			successor = v;
		}

		public void split(Vertex v) {
			mail_aa_extra_splay_tl.this.split(root, v.h);
			Tree right = split[1];
			mail_aa_extra_splay_tl.this.split(split[0], v.h - 1);
			paths[0] = createPath(split[0], successor);
			paths[1] = createPath(split[1], rightest(split[0]));
			paths[2] = createPath(right, v);
			for (int i = 0; i < paths.length; i++) {
				if (paths[i] != null) {
					paths[i].update();
				}
			}
		}

		private void update() {
			root.path = this;
		}

		private Vertex rightest(Tree t) {
			while (t != null && t.right != null) {
				t = t.right;
			}
			return t == null ? null : t.v;
		}
	}

	private Path createPath(Tree t, Vertex v) {
		if (t == null) {
			return null;
		}
		return new Path(t, v);
	}

	class Vertex {

		@Override
		public String toString() {
			return "" + n;
		}

		public Vertex(int i, int v) {
			n = i;
			val = v;
		}

		Tree t;
		int n;
		int h;
		int val;
		Vertex parent;
		boolean u;
	}

	Random rand = new Random(135235);

	class Tree {
		Tree left, right, parent;
		int max;
		Vertex v;
		Path path;

		@Override
		public String toString() {
			String s = "";
			if (left != null) {
				s += left + " ";
			}
			s += v;
			if (right != null) {
				s += " " + right;
			}
			return s;
		}

		public Tree(Vertex v) {
			this.v = v;
			max = v.val;
			path = null;
		}

		public void setValue(int val) {
			v.val = val;
			Path p = path;
			update();
			path = p;
		}

		public void update() {
			path = null;
			parent = null;
			max = v.val;
			if (left != null) {
				max = Math.max(max, left.max);
				left.parent = this;
			}
			if (right != null) {
				max = Math.max(max, right.max);
				right.parent = this;
			}
		}
	}

	Tree merge(Tree t1, Tree t2) {
		if (t1 == null) {
			return t2;
		}
		t1 = rightest(t1);
		splay(t1);
		t1.right = t2;
		t1.update();
		return t1;
	}

	private void splay(Tree x) {
		Path path = getPath(x.v);
		while (true) {
			Tree p = x.parent;
			if (p == null) {
				break;
			}
			Tree g = p == null ? null : p.parent;
			if (g == null) {
				if (p.left == x) {
					p.left = x.right;
					x.right = p;
					p.update();
					x.update();
				} else {
					p.right = x.left;
					x.left = p;
					p.update();
					x.update();
				}
				continue;
			}
			Tree gg = g == null ? null : g.parent;
			if (p.left == x) {
				if (g.left == p) {
					g.left = p.right;
					p.left = x.right;
					x.right = p;
					p.right = g;
				} else {
					g.right = x.left;
					p.left = x.right;
					x.left = g;
					x.right = p;
				}
			} else {
				if (g.left == p) {
					g.left = x.right;
					p.right = x.left;
					x.right = g;
					x.left = p;
				} else {
					g.right = p.left;
					p.right = x.left;
					x.left = p;
					p.left = g;
				}
			}
			g.update();
			p.update();
			x.update();
			x.parent = gg;
			if (x.parent != null) {
				if (x.parent.v.h < x.v.h) {
					x.parent.right = x;
				} else {
					x.parent.left = x;
				}
			}
		}
		x.update();
		x.path = path;
		path.root = x;
	}

	private Tree rightest(Tree t) {
		while (t != null && t.right != null) {
			t = t.right;
		}
		return t;
	}

	void split(Tree t, int h) {
		if (t == null) {
			split[0] = split[1] = null;
			return;
		}
		if (t.v.h <= h) {
			split(t.right, h);
			t.right = split[0];
			split[0] = t;
		} else {
			split(t.left, h);
			t.left = split[1];
			split[1] = t;
		}
		for (int i = 0; i < split.length; i++) {
			if (split[i] != null) {
				split[i].update();
			}
		}
	}

	Path expose(Vertex v) {
		Path p = null;
		while (v != null) {
			Path q = getPath(v);
			Vertex w = q.successor;
			q.split(v);
			p = join(join(paths[0], paths[1]), p);
			v = w;
		}
		return p;
	}

	private Path join(Path p1, Path p2) {
		if (p1 == null) {
			return p2;
		}
		if (p2 == null) {
			return p1;
		}
		return createPath(merge(p1.root, p2.root), p1.successor);
	}

	private Path getPath(Vertex v) {
		Tree t = v.t;
		while (t.parent != null) {
			t = t.parent;
		}
		return t.path;
	}
}
