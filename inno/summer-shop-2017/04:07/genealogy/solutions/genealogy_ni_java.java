import static java.lang.Math.*;
import java.io.*;
import java.math.*;
import java.util.*;

public class genealogy_ni_java {
	MyScanner in;
	PrintWriter out;

	int n;
	int root;
	ArrayList<Integer> edges[];

	@SuppressWarnings("unchecked")
	void load() throws Exception {
		n = in.nextInt();
		edges = new ArrayList[n];
		for (int i = 0; i < n; i++) {
			edges[i] = new ArrayList<Integer>();
		}

		for (int i = 0; i < n; i++) {
			int p = in.nextInt();
			if (p == -1) {
				root = i;
			} else {
				edges[p - 1].add(i);
			}
		}
	}

	void solve() throws Exception {
		prepare();

		int q = in.nextInt();
		for (int i = 0; i < q; i++) {
			int k = in.nextInt();
			Integer query[] = new Integer[k];
			for (int j = 0; j < k; j++) {
				query[j] = in.nextInt() - 1;
			}
			out.println(get(query));
		}
	}

	int get(Integer query[]) {
		Arrays.sort(query, new Comparator<Integer>() {

			public int compare(Integer a, Integer b) {
				return first[a] - first[b];
			}
		});

		int res = depth[query[0]] + 1;
		for (int i = 1; i < query.length; i++) {
			int s = lca(query[i - 1], query[i]);
			res += depth[query[i]] - depth[s];
		}

		return res;
	}

	int lca(int u, int v) {
		int pu = first[u];
		int pv = first[v];
		
		if (pu > pv) {
			int t = pu;
			pu = pv;
			pv = t;
		}
		
		int k = log2[pv - pu + 1];
		int a = sparse[k][pu];
		int b = sparse[k][pv - (1 << k) + 1];
		return depth[a] < depth[b] ? a : b;
	}

	int sparse[][];
	int log2[];

	void prepare() {
		depth = new int[n];
		first = new int[n];
		order = new ArrayList<Integer>();
		dfs(root, 0);

		log2 = new int[order.size() + 1];
		log2[1] = 0;
		for (int i = 2; i <= order.size(); i++) {
			log2[i] = log2[i >> 1] + 1;
		}

		sparse = new int[log2[order.size()] + 1][];
		for (int j = 0; j < sparse.length; j++) {
			sparse[j] = new int[order.size() - (1 << j) + 1];
			for (int i = 0; i < sparse[j].length; i++) {
				if (j == 0) {
					sparse[j][i] = order.get(i);
				} else {
					int a = sparse[j - 1][i];
					int b = sparse[j - 1][i + (1 << (j - 1))];
					sparse[j][i] = depth[a] < depth[b] ? a : b;
				}
			}
		}
	}

	int depth[];
	int first[];
	ArrayList<Integer> order;

	void dfs(int v, int d) {
		depth[v] = d;
		order.add(v);
		first[v] = order.size() - 1;
		for (int u : edges[v]) {
			dfs(u, d + 1);
			order.add(v);
		}
	}

	final String TASK = "genealogy";

	public void run() {
		try {
			in = new MyScanner(TASK + ".in");
			out = new PrintWriter(TASK + ".out");
			load();
			solve();
			out.close();
		} catch (Exception e) {
			e.printStackTrace();
			System.exit(42);
		}
	}

	public static void main(String[] args) {
		new genealogy_ni_java().run();
	}

	class MyScanner {
		BufferedReader br;
		StringTokenizer st;

		MyScanner(String file) {
			try {
				br = new BufferedReader(new FileReader(new File(file)));
			} catch (FileNotFoundException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
				System.exit(42);
			}
		}

		MyScanner() {
			try {
				br = new BufferedReader(new InputStreamReader(System.in));
			} catch (Exception e) {
				e.printStackTrace();
				System.exit(42);
			}
		}

		String nextToken() throws Exception {
			while (st == null || (!st.hasMoreTokens())) {
				st = new StringTokenizer(br.readLine());
			}
			return st.nextToken();
		}

		int nextInt() throws Exception {
			return Integer.parseInt(nextToken());
		}

		double nextDouble() throws Exception {
			return Double.parseDouble(nextToken());
		}

		long nextLong() throws Exception {
			return Long.parseLong(nextToken());
		}

		BigInteger nextBigInteger(int radix) throws Exception {
			return new BigInteger(nextToken(), radix);
		}
	}

}
