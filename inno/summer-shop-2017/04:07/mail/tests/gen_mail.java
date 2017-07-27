import java.io.IOException;
import java.io.PrintWriter;
import java.util.Arrays;
import java.util.Random;

public class gen_mail {

	static PrintWriter out;
	static Random rand = new Random(15435732);
	static final int tests = 50;
	static final int SMALLN = 100;
	static final int SMALLK = 100;
	static final int MAXH = 100000;
	static final int MAXN = 50000;
	static final int MAXK = 100000;

	public static void main(String[] args) throws IOException {
		smallTests();
		hugeTests();
		difficultTests();
	}

	private static void hugeTests() throws IOException {
		for (int test = 1; test <= 2 * tests / 5; test++) {
			int testn = test + tests / 5;
			out = new PrintWriter((testn / 10) + "" + (testn % 10));
			switch (test) {
			case 1:
				lineTest(MAXN, MAXK, false);
				break;
			case 2:
				hugeReqLineTest(MAXN, MAXK, false);
				break;
			case 3:
				almostFullTree(MAXN, MAXK, false);
				break;
			case 4:
				strangeTest(MAXN, MAXK);
			case 5:
				reverseStrangeTest(MAXN, MAXK);

			default:
				randomTest(MAXN, MAXK, false);
				break;
			}
			out.close();
		}
	}

	private static void strangeTest(int n, int k) {
		out.println(n);
		for (int i = 0; i < n; i++) {
			if (i > 0) {
				out.print(" ");
			}
			if (i % 2 == 0) {
				out.print("1");
			} else {
				out.print(i + 1);
			}
		}
		out.println();
		out.println("1 2");
		out.println("3 2");
		for (int i = 3; i + 1 < n; i += 2) {
			out.println((i - 1) + " " + (i + 1));
			out.println((i + 1) + " " + (i + 2));
		}
		if (n % 2 == 0) {
			out.println(n + " " + (n - 1));
		}
		out.println(k);
		for (int i = 0; i < k; i++) {
			int x = 2 * i % n;
			out.println("? 1 " + (x + 1));
		}
	}

	private static void reverseStrangeTest(int n, int k) {
		out.println(n);
		for (int i = 0; i < n; i++) {
			if (i > 0) {
				out.print(" ");
			}
			if (i % 2 == 0) {
				out.print("1");
			} else {
				out.print(i + 1);
			}
		}
		out.println();
		out.println("1 2");
		out.println("3 2");
		for (int i = 3; i + 1 < n; i += 2) {
			out.println((i - 1) + " " + (i + 1));
			out.println((i + 1) + " " + (i + 2));
		}
		if (n % 2 == 0) {
			out.println(n + " " + (n - 1));
		}
		out.println(k);
		for (int i = 0; i < k; i++) {
			int x = ((n - 2 * i) % n + n) % n;
			out.println("? 1 " + (x + 1));
		}
	}

	private static void difficultTests() throws IOException {
		for (int test = 1; test <= 2 * tests / 5; test++) {
			int testn = test + 3 * tests / 5;
			out = new PrintWriter((testn / 10) + "" + (testn % 10));
			switch (test) {
			case 1:
				lineTest(MAXN, MAXK, true);
				break;
			case 2:
				hugeReqLineTest(MAXN, MAXK, true);
				break;
			case 3:
				almostFullTree(MAXN, MAXK, true);
				break;
			case 4:
				randomWithALotOfChanges(MAXN, MAXK);
				break;

			default:
				randomTest(MAXN, MAXK, true);
				break;
			}
			out.close();
		}
	}

	private static void randomWithALotOfChanges(int n, int k) {
		int[] a = randomTree(n);
		int[] h = randomHeights(n);
		out.println(n);
		println(h);
		for (int i = 0; i < a.length; i++) {
			if (a[i] != -1) {
				out.println((i + 1) + " " + (a[i] + 1));
			}
		}
		out.println(k);
		for (int i = 0; i < k; i++) {
			if (i < 3 * k / 4) {
				out.println("! " + (1 + rand.nextInt(n)) + " "
						+ (1 + rand.nextInt(MAXH)));
			} else {
				out.println("? " + (1 + rand.nextInt(n)) + " "
						+ (1 + rand.nextInt(n)));
			}
		}
	}

	private static void smallTests() throws IOException {
		for (int test = 1; test <= tests / 5; test++) {
			out = new PrintWriter((test / 10) + "" + (test % 10));
			switch (test) {
			case 1:
				lineTest(SMALLN, SMALLK, true);
				break;
			case 2:
				hugeReqLineTest(SMALLN, SMALLK, true);
				break;
			case 3:
				almostFullTree(SMALLN, SMALLK, true);
				break;

			default:
				randomTest(SMALLN, SMALLK, true);
				break;
			}
			out.close();
		}
	}

	private static void almostFullTree(int n, int k, boolean change) {
		out.println(n);
		println(randomHeights(n));
		int[] a = randomPerm(n);
		for (int i = 1; i < a.length; i++) {
			out.println((a[i] + 1) + " " + (a[(i - 1) / 2] + 1));
		}
		out.println(k);
		for (int i = 0; i < k; i++) {
			if (change && rand.nextBoolean()) {
				out.println("! " + (1 + rand.nextInt(n)) + " "
						+ (1 + rand.nextInt(MAXH)));
			} else {
				int x = 1 + rand.nextInt(n / 4) - 1;
				int y = n - rand.nextInt(n / 4) - 1;
				out.println("? " + (1 + a[x]) + " " + (1 + a[y]));
			}
		}
	}

	private static void hugeReqLineTest(int n, int k, boolean change) {
		out.println(n);
		println(randomHeights(n));
		int[] a = randomPerm(n);
		for (int i = 0; i + 1 < a.length; i++) {
			out.println((a[i] + 1) + " " + (a[i + 1] + 1));
		}
		out.println(k);
		for (int i = 0; i < k; i++) {
			if (change && rand.nextInt(4) == 0) {
				out.println("! " + (1 + rand.nextInt(n)) + " "
						+ (1 + rand.nextInt(MAXH)));
			} else {
				int x = 1 + rand.nextInt(n / 4) - 1;
				int y = n - rand.nextInt(n / 4) - 1;
				out.println("? " + (1 + a[x]) + " " + (1 + a[y]));
			}
		}
	}

	private static void lineTest(int n, int k, boolean change) {
		out.println(n);
		println(randomHeights(n));
		int[] a = randomPerm(n);
		for (int i = 0; i + 1 < a.length; i++) {
			out.println((a[i] + 1) + " " + (a[i + 1] + 1));
		}
		out.println(k);
		for (int i = 0; i < k; i++) {
			if (change && rand.nextBoolean()) {
				out.println("! " + (1 + rand.nextInt(n)) + " "
						+ (1 + rand.nextInt(MAXH)));
			} else {
				out.println("? " + (1 + rand.nextInt(n)) + " "
						+ (1 + rand.nextInt(n)));
			}
		}
	}

	private static void randomTest(int n, int k, boolean change) {
		int[] a = randomTree(n);
		int[] h = randomHeights(n);
		out.println(n);
		println(h);
		for (int i = 0; i < a.length; i++) {
			if (a[i] != -1) {
				out.println((i + 1) + " " + (a[i] + 1));
			}
		}
		out.println(k);
		for (int i = 0; i < k; i++) {
			if (change && rand.nextBoolean()) {
				out.println("! " + (1 + rand.nextInt(n)) + " "
						+ (1 + rand.nextInt(MAXH)));
			} else {
				out.println("? " + (1 + rand.nextInt(n)) + " "
						+ (1 + rand.nextInt(n)));
			}
		}
	}

	private static void println(int[] a) {
		for (int i = 0; i < a.length; i++) {
			if (i > 0) {
				out.print(" ");
			}
			out.print(a[i]);
		}
		out.println();
	}

	private static int[] randomHeights(int n) {
		int[] a = new int[n];
		for (int i = 0; i < a.length; i++) {
			a[i] = 1 + rand.nextInt(MAXH);
		}
		return a;
	}

	private static int[] randomTree(int n) {
		int[] a = new int[n];
		a[0] = -1;
		for (int i = 1; i < a.length; i++) {
			a[i] = rand.nextInt(i);
		}
		int[] perm = randomPerm(n);
		int[] b = new int[n];
		Arrays.fill(b, -1);
		for (int i = 0; i < a.length; i++) {
			if (a[i] != -1) {
				b[perm[i]] = perm[a[i]];
			}
		}
		return b;
	}

	private static int[] randomPerm(int n) {
		int[] a = new int[n];
		for (int i = 0; i < a.length; i++) {
			a[i] = i;
			int j = rand.nextInt(i + 1);
			int tmp = a[i];
			a[i] = a[j];
			a[j] = tmp;
		}
		return a;
	}
}
