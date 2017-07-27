import java.util.List; 
import java.util.Arrays; 
import java.util.ArrayList; 
import java.util.Comparator; 
import java.util.Collections; 

/** 
 * Built using CHelper plug-in 
 * Actual solution is at the top 
 * @author Egor Kulikov (egor@egork.net) 
 */ 
public class KingSort { 
  public String[] getSortedList(String[] kings) { 
    Arrays.sort(kings, new Comparator<String>() { 
      public int compare(String o1, String o2) { 
        String[] first = o1.split(" "); 
        String[] second = o2.split(" "); 
        if (first[0].compareTo(second[0]) != 0) 
          return first[0].compareTo(second[0]); 
        return MiscUtils.convertFromRoman(first[1]) - MiscUtils.convertFromRoman(second[1]); 
      } 
    }); 
    return kings; 
  } 


} 

class MiscUtils { 

  private static final String[] ROMAN_TOKENS = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"}; 
  private static final int[] ROMAN_VALUES = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1}; 

  public static int convertFromRoman(String number) { 
    int result = 0; 
    for (int i = 0; i < ROMAN_TOKENS.length; i++) { 
      while (number.startsWith(ROMAN_TOKENS[i])) { 
        number = number.substring(ROMAN_TOKENS[i].length()); 
        result += ROMAN_VALUES[i]; 
      } 
    } 
    return result; 
  } 

} 

public class Main {
	public static void main(String[] args) {
		InputStream inputStream = System.in;
		OutputStream outputStream = System.out;
		FastScanner in = new FastScanner(inputStream);
		FastPrinter out = new FastPrinter(outputStream);

        int n = in.readInt();
        String[] s = new String[n];
        for (int i = 0; i < n; ++i) {
            s[i] = in.readLine();
        }

		KingSort solver = new KingSort(s);
		String[] ans = solver.getSortedList();

        for (int i = 0; i < ans.length; ++i) {
            out.println(ans[i]);
        }

		out.close();
	}
}


class FastScanner extends BufferedReader {

    public FastScanner(InputStream is) {
        super(new InputStreamReader(is));
    }

    public int read() {
        try {
            int ret = super.read();
//            if (isEOF && ret < 0) {
//                throw new InputMismatchException();
//            }
//            isEOF = ret == -1;
            return ret;
        } catch (IOException e) {
            throw new InputMismatchException();
        }
    }

    static boolean isWhiteSpace(int c) {
        return c >= 0 && c <= 32;
    }

    public int nextInt() {
        int c = read();
        while (isWhiteSpace(c)) {
            c = read();
        }
        int sgn = 1;
        if (c == '-') {
            sgn = -1;
            c = read();
        }
        int ret = 0;
        while (c >= 0 && !isWhiteSpace(c)) {
            if (c < '0' || c > '9') {
                throw new NumberFormatException("digit expected " + (char) c
                        + " found");
            }
            ret = ret * 10 + c - '0';
            c = read();
        }
        return ret * sgn;
    }

    public String readLine() {
        try {
            return super.readLine();
        } catch (IOException e) {
            return null;
        }
    }

    }

class FastPrinter extends PrintWriter {

    public FastPrinter(OutputStream out) {
        super(out);
    }

    public FastPrinter(Writer out) {
        super(out);
    }


}

