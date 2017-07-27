import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collection;
import java.util.Collections;
import java.util.Random;

public class TestGen {
	class DSU {
		int[] p, r;

		public DSU(int n) {
			p = new int[n];
			for (int i = 0; i < p.length; i++) {
				p[i] = i;
			}
			r = new int[n];
		}

		int get(int x) {
			if (p[x] == x)
				return x;
			return p[x] = get(p[x]);
		}

		void union(int a, int b) {
			a = get(a);
			b = get(b);
			if (a == b)
				throw new AssertionError();
			if (r[a] > r[b]) {
				p[b] = a;
			} else if (r[a] < r[b]) {
				p[a] = b;
			} else {
				p[a] = b;
				r[b]++;
			}
		}
	}

	class Pair {
		int x, y;

		public Pair(int x, int y) {
			this.x = x;
			this.y = y;
		}

	}

	class Test {
		ArrayList<Pair> tree;
		ArrayList<Pair> req;

		public Test(ArrayList<Pair> tree, ArrayList<Pair> req) {
			this.tree = tree;
			this.req = req;
		}

	}

	private static int testCount = 0;

	private void write(Test t) {
		try {
			++testCount;
			String filename = testCount / 10 + "" + testCount % 10;
			PrintWriter out = new PrintWriter(filename);
			out.println(t.tree.size() + 1);
			for (Pair p : t.tree) {
				out.println((p.x + 1) + " " + (p.y + 1));
			}
			out.println(t.req.size());
			for (Pair p : t.req) {
				out.println((p.x + 1) + " " + (p.y + 1));
			}
			System.err.println(testCount);
			out.flush();
			out.close();
		} catch (IOException ex) {
			throw new RuntimeException(ex);
		}
	}

	void myAssert(boolean b) {
		if (!b)
			throw new AssertionError();
	}

	static Random rand = new Random(1);

	public void run() throws IOException {





		write(genTest(2, 1));// 0
		write(genTest(10, 5));
		write(genTestWithUnusedInternalEdges(10, 3, 2));
		write(genTestLine(10, 5));
		write(genTestHedgehog(10, 100));// 0
		write(genTestHedgehog(10, 3));
		write(genTest(100, 50));
		write(genTestWithUnusedInternalEdges(100, 100, 3));
		write(genTestWithUnusedInternalEdges(rand.nextInt(100) + 1, rand.nextInt(100) + 1, rand.nextInt(10)));
		write(genTestWithUnusedInternalEdges(rand.nextInt(100) + 1, rand.nextInt(100) + 1, rand.nextInt(10)));
		write(genTestWithUnusedInternalEdges(100, 100, 10));
		write(genTestLine(100, 100));

		write(genTestHedgehog(1000, 1000));
		write(genTestWithUnusedInternalEdges(1000, 1000, 10));
		write(genTestLine(1000, 10));
		write(genTestWithUnusedInternalEdges(1000, 1000, 3));

//		write(genTest(100000, 1));
//		write(genTestWithUnusedInternalEdges(100000, 100000, 100));
//		write(genTest(100000, 100000));
//		write(genTestWithUnusedInternalEdges(100000, 100000, 1));
		write(genTestHighTree(100000, 50000));
		write(genTestLineRandom(100000, 70000));
		write(genTestLineRandom(100000, 90000));
		write(genTestHighTree(100000, 100000));
	}

	Test genTest(int n, int m) {
		return new Test(genTree(n), genRandomRequest(n, m));
	}

	Test genTestLine(int n, int m) {
		return new Test(genTreeLine(n), genRandomRequest(n, m));
	}

	Test genTestHedgehog(int n, int m) {
		return new Test(genTreeHedgehog(n), genRandomRequest(n, m));
	}

	Test genTestHighTree(int n, int m) {
		return new Test(genHighTree(n), genRandomRequest(n, m));
	}

	Test genTestLineRandom(int n, int m) {
		return new Test(genTreeRandomLine(n), genRandomRequest(n, m));
	}

	ArrayList<Pair> genTree(int n) {
		ArrayList<Pair> res = new ArrayList<Pair>();
		DSU dsu = new DSU(n);
		for (int i = 0; i < n - 1; i++) {
			int x, y;
			do {
				x = rand.nextInt(n);
				y = rand.nextInt(n);
			} while (dsu.get(x) == dsu.get(y));
			dsu.union(x, y);
			res.add(new Pair(x, y));
		}
		return res;
	}

	Test genTestWithUnusedInternalEdges(int n, int m, int k) {
		ArrayList<Pair> tree = new ArrayList<Pair>();
		DSU dsu = new DSU(n);
		ArrayList<Pair> forb = new ArrayList<Pair>();
		for (int i = 0; i < k; i++) {
			int x, y;
			do {
				x = rand.nextInt(n);
				y = rand.nextInt(n);
			} while (dsu.get(x) == dsu.get(y));
			dsu.union(x, y);
			forb.add(new Pair(x, y));
		}
		dsu = new DSU(n);
		for (int i = 0; i < n - 1 - k; i++) {
			int x, y;
			wh: do {
				x = rand.nextInt(n);
				y = rand.nextInt(n);
				if (dsu.get(x) == dsu.get(y))
					continue;
				for (Pair p : forb) {
					if ((dsu.get(x) == dsu.get(p.x) && dsu.get(y) == dsu.get(p.y)) || (dsu.get(x) == dsu.get(p.y) && dsu.get(y) == dsu.get(p.x))) {
						continue wh;
					}
				}
				break;
			} while (true);
			dsu.union(x, y);
			tree.add(new Pair(x, y));
		}
		ArrayList<Pair> req = new ArrayList<Pair>();
		for (int i = 0; i < m; i++) {
			int x, y;
			do {
				x = rand.nextInt(n);
				y = rand.nextInt(n);
			} while (x == y || dsu.get(x) != dsu.get(y));
			req.add(new Pair(x, y));
		}
		for (int i = 0; i < k; i++) {
			int x, y;
			do {
				x = rand.nextInt(n);
				y = rand.nextInt(n);
			} while (dsu.get(x) == dsu.get(y));
			dsu.union(x, y);
			tree.add(new Pair(x, y));
		}
		return new Test(tree, req);
	}

	ArrayList<Pair> genTreeLine(int n) {
		ArrayList<Pair> res = new ArrayList<Pair>();
		for (int i = 0; i < n - 1; i++) {
			if (rand.nextBoolean()) {
				res.add(new Pair(i, i + 1));
			} else {
				res.add(new Pair(i + 1, i));
			}
		}
		Collections.shuffle(res, rand);
		return res;
	}

	ArrayList<Pair> genHighTree(int n) {
		int m = n - n / 5;
		ArrayList<Pair> res = genTreeLine(m);
		for (int i = m; i < n; i++) {
			int x = rand.nextInt(i);
			if (rand.nextBoolean()) {
				res.add(new Pair(x, i));
			} else {
				res.add(new Pair(i, x));
			}
		}
		Collections.shuffle(res, rand);
		return res;
	}

	ArrayList<Pair> genTreeRandomLine(int n) {
		int m = n - n / 5;
		ArrayList<Pair> res = genTreeLine(m);
		int k1 = (n - m) / 2;
		int k2 = n - m - k1;
		ArrayList<Pair> first = genTree(k1);
		ArrayList<Pair> second = genTree(k2);
		for (Pair p : first) {
			p.x += m;
			p.y += m;
			res.add(p);
		}
		for (Pair p : second) {
			p.x += m + k1;
			p.y += m + k2;
			res.add(p);
		}
		if (rand.nextBoolean()) {
			res.add(new Pair(0, m));
		} else {
			res.add(new Pair(m, 0));
		}
		if (rand.nextBoolean()) {
			res.add(new Pair(m - 1, m + k1));
		} else {
			res.add(new Pair(m + k1, m - 1));
		}
		Collections.shuffle(res, rand);
		return res;
	}

	ArrayList<Pair> genTreeHedgehog(int n) {
		ArrayList<Pair> res = new ArrayList<Pair>();
		int center = rand.nextInt(n);
		for (int i = 0; i < n; i++) {
			if (i == center)
				continue;
			if (rand.nextBoolean()) {
				res.add(new Pair(i, center));
			} else {
				res.add(new Pair(center, i));
			}
		}
		Collections.shuffle(res, rand);
		return res;
	}

	ArrayList<Pair> genRandomRequest(int n, int m) {
		ArrayList<Pair> res = new ArrayList<Pair>();
		for (int i = 0; i < m; i++) {
			int x, y;
			do {
				x = rand.nextInt(n);
				y = rand.nextInt(n);
			} while (x == y);
			res.add(new Pair(x, y));
		}
		return res;
	}

	ArrayList<Pair> genRandomRequestAntiZero(int n, int m) {
		ArrayList<Pair> res = new ArrayList<Pair>();
		int cnt = rand.nextInt(Math.min(n, 10));
		for (int i = 0; i < m; i++) {
			int x, y;
			do {
				x = rand.nextInt(n - cnt);
				y = rand.nextInt(n - cnt);
			} while (x == y);
			res.add(new Pair(x, y));
		}
		return res;
	}

	public static void main(String[] args) throws IOException {
		if (args.length > 0) {
			testCount = Integer.valueOf(args[0]);
		}
		new TestGen().run();
	}

}
