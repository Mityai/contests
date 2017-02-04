import java.io.*;

class a {
  public static void main( String[] args ) throws Exception {
    PrintWriter out = new PrintWriter(new FileOutputStream("a.out", true), true);
    out.print("abc");
  }
}
