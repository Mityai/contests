import java.io.*;
import java.util.*;
import java.math.*;

public class mail_nn {

	void solve() {
		int n = sc.nextInt();
		LinkingCuttingTree tree = new LinkingCuttingTree(n);
		for (int i = 0; i < n; i++) {
			int h = sc.nextInt();
			tree.updateHeight(i, h);
		}
		for (int i = 0; i + 1 < n; i++) {
			int u = sc.nextInt() - 1;
			int v = sc.nextInt() - 1;
			tree.link(u, v);
		}
		int q = sc.nextInt();
		for (int i = 0; i < q; i++) {
			char ch = sc.nextToken().charAt(0);
			if (ch == '!') {
				int x = sc.nextInt() - 1;
				int h = sc.nextInt();
				tree.updateHeight(x, h);
			} else if (ch == '?') {
				int x = sc.nextInt() - 1;
				int y = sc.nextInt() - 1;
				out.println(tree.getMaxHeight(x, y));
			} else {

			}
		}
	}

	FastScanner sc;
	PrintWriter out;

	public void run() {
		Locale.setDefault(Locale.US);
		try {
			sc = new FastScanner("mail.in");
			out = new PrintWriter("mail.out");
			solve();
			sc.close();
			out.close();
		} catch (Throwable e) {
			e.printStackTrace();
			System.exit(1);
		}
	}

	class FastScanner extends BufferedReader {
		StringTokenizer st;
		boolean eof;
		String buf;
		String curLine;
		boolean createST;

		public FastScanner(String fileName) throws FileNotFoundException {
			this(fileName, true);
		}

		public FastScanner(String fileName, boolean createST)
				throws FileNotFoundException {
			super(new FileReader(fileName));
			this.createST = createST;
			nextToken();
		}

		public FastScanner(InputStream stream) {
			this(stream, true);
		}

		public FastScanner(InputStream stream, boolean createST) {
			super(new InputStreamReader(stream));
			this.createST = createST;
			nextToken();
		}

		String nextLine() {
			String ret = curLine;
			if (createST) {
				st = null;
			}
			nextToken();
			return ret;
		}

		String nextToken() {
			if (!createST) {
				try {
					curLine = readLine();
				} catch (Exception e) {
					eof = true;
				}
				return null;
			}
			while (st == null || !st.hasMoreTokens()) {
				try {
					curLine = readLine();
					st = new StringTokenizer(curLine);
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

		BigInteger nextBigInteger() {
			return new BigInteger(nextToken());
		}

		public void close() {
			try {
				buf = null;
				st = null;
				curLine = null;
				super.close();
			} catch (Exception e) {

			}
		}

		boolean isEOF() {
			return eof;
		}
	}

	public static void main(String[] args) {
		new mail_nn().run();
	}
}

class LinkingCuttingTree {
	Node[] nodes;
    Node[] toUse;
	int n;

	public LinkingCuttingTree(int n) {
		this.n = n;
		nodes = new Node[n];
		for (int i = 0; i < nodes.length; i++) {
			nodes[i] = new Node(0);
		}
        toUse = new Node[2];
	}

	void updateHeight(int x, int h) {
		Node v = nodes[x];
		v.height = h;
		while (v != null) {
			Node.getUp(v);
			v = v.parent;
		}
	}

	public void link(int x, int y) {
		Node v1 = nodes[x];
		Node v2 = nodes[y];
		evert(v2);
		Node.setHigherPath(v2, v1);
	}

	public void evert(Node v) {
		expose(v);
		Node.reverse(v);
	}

	public void expose(Node v) {
		splitDown(v);
		while (Node.getHigherPath(v) != null) {
			splice(v);
		}
	}

	void splice(Node v) {
		Node higher = Node.getHigherPath(v);
		if (higher == null) {
			throw new AssertionError("higher == null");
		}
		splitDown(higher);
		mergePaths(v, higher);
	}

	private void splitDown(Node v) {
		Node.tracePath(v);
		int k = Node.getNum(v);
		Node h = Node.getHigherPath(v);
		Node[] t = Node.split(Node.getRoot(v), k - 1, toUse);
		if (t[0] != null) {
			Node.setHigherPath(t[0], v);
		}
		Node.setHigherPath(v, h);
	}

	private void mergePaths(Node v, Node u) {
		v = Node.getRoot(v);
		u = Node.getRoot(u);
		if (v == u) {
			return;
		}
		Node higher = Node.getHigherPath(u);
		Node.merge(v, u);
		Node.setHigherPath(v, higher);
	}

	public int getMaxHeight(int x, int y) {
		if (x == y) {
			return nodes[x].height;
		}
		Node v1 = nodes[x];
		Node v2 = nodes[y];
		evert(v1);
		expose(v2);
		return Node.getMaxHeight(Node.getRoot(v1));
	}

}

class Node {
	final private static Random rand = new Random("treapRandom".hashCode());
	Node left;
	Node right;
	Node parent;
	boolean toReverse;
	int height;
	int maxHeight;
	int count;
	int priority;
	private Node higherPath;

	static Node getHigherPath(Node v) {
		if (v == null) {
			return null;
		}
		v = getRoot(v);
		return v.higherPath;
	}

	static void setHigherPath(Node v, Node h) {
		if (v == null) {
			return;
		}
		v = getRoot(v);
		v.higherPath = h;
	}

	static void setReverse(Node v) {
		if (v == null) {
			return;
		}
		v.toReverse = !v.toReverse;
	}

	static int getNum(Node v) {
		if (v == null) {
			return 0;
		}
		int ret = getCount(v.left) + 1;
		Node last = v;
		v = v.parent;
		while (v != null) {
			if (v.right == last) {
				ret += getCount(v.left) + 1;
			}
			last = v;
			v = v.parent;
		}
		return ret;
	}

	static void tracePath(Node v) {
		if (v == null) {
			return;
		}
		tracePath(v.parent);
		relax(v);
	}

	static void reverse(Node v) {
		v = getRoot(v);
		setReverse(v);
	}

	static Node getRoot(Node v) {
		while (v.parent != null) {
			v = v.parent;
		}
		return v;
	}

	static void getUp(Node v) {
		if (v == null) {
			return;
		}
		v.count = getCount(v.left) + getCount(v.right) + 1;
		v.maxHeight = Math.max(v.height,
				Math.max(getMaxHeight(v.left), getMaxHeight(v.right)));
	}

	static void setLeft(Node v, Node x) {
		v.left = x;
		if (x != null) {
			x.parent = v;
		}
	}

	static void setRight(Node v, Node x) {
		v.right = x;
		if (x != null) {
			x.parent = v;
		}
	}

	static int getCount(Node v) {
		return v == null ? 0 : v.count;
	}

	static int getMaxHeight(Node v) {
		return v == null ? Integer.MIN_VALUE : v.maxHeight;
	}

	public Node(int h) {
		count = 1;
		priority = rand.nextInt();
		height = h;
		maxHeight = h;
		left = right = parent = null;
		toReverse = false;
	}

	static void relax(Node v) {
		if (v.toReverse) {
			Node t = v.left;
			v.left = v.right;
			v.right = t;
			setReverse(v.left);
			setReverse(v.right);
			v.toReverse = false;
		}
	}

	static Node merge(Node l, Node r) {
		if (l == null) {
			return r;
		}
		if (r == null) {
			return l;
		}
		relax(l);
		relax(r);
		Node ret;
		if (l.priority > r.priority) {
			ret = l;
			setRight(ret, merge(l.right, r));
		} else {
			ret = r;
			setLeft(ret, merge(l, r.left));
		}
		nullUp(ret);
		getUp(ret);
		return ret;
	}

	static Node[] split(Node v, int k, Node[] array) {
		if (v == null) {
            array[0] = array[1] = null;
			return array;
		}
		relax(v);
		Node[] ret;
		if (getCount(v.left) + 1 <= k) {
			ret = split(v.right, k - getCount(v.left) - 1, array);
			setRight(v, ret[0]);
			ret[0] = v;
		} else {
			ret = split(v.left, k, array);
			setLeft(v, ret[1]);
			ret[1] = v;
		}
		nullUp(ret[0]);
		nullUp(ret[1]);
		getUp(ret[0]);
		getUp(ret[1]);
		return ret;
	}

	static void nullUp(Node v) {
		if (v != null) {
			v.parent = null;
		}
	}

	@Override
	public String toString() {
		return "Node [left=" + left + ", right=" + right + ", height=" + height
				+ ", maxHeight=" + maxHeight + ", count=" + count
				+ ", higher = "
				+ (higherPath == null ? "null" : higherPath.height) + "]";
	}
}