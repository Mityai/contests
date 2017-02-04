
/**
 * Author: Sergey Kopeliovich (Burunduk30@gmail.com)
 * (translated from C++ by Pavel Mavrin)
 */

class SuffixAutomaton {

    public static final int ALPHA_SIZE = 27;
    public int root, last, n;
    public final int len[], suf[], next[];

    public SuffixAutomaton(String s) {
        len = new int[2 * s.length() + 2];
        suf = new int[2 * s.length() + 2];
        //compressed 2d array. next[i][j] -> next[i * ALPHA_SIZE + j];
        next = new int[(2 * s.length() + 2) * ALPHA_SIZE];
        for (int i = 0; i < ALPHA_SIZE; i++)
            next[i] = 1;
        n = 1;
        root = last = newV(0, 0);
        for (int i = 0; i < s.length(); i++) {
            int ch = s.charAt(i) - 'a';
            int R, Q, P = last;
            last = newV(len[last] + 1, 0);
            while (next[P * ALPHA_SIZE + ch] == 0) {
                next[P * ALPHA_SIZE + ch] = last;
                P = suf[P];
            }
            if (P == 0)
                suf[last] = 1;
            else if (len[Q = next[P * ALPHA_SIZE + ch]] == len[P] + 1)
                suf[last] = Q;
            else {
                R = newV(len[P] + 1, suf[Q]);
                suf[last] = suf[Q] = R;
                System.arraycopy(next, Q * ALPHA_SIZE, next, R * ALPHA_SIZE, ALPHA_SIZE);
                while (P > 0 && next[P * ALPHA_SIZE + ch] == Q) {
                    next[P * ALPHA_SIZE + ch] = R;
                    P = suf[P];
                }
            }
        }
    }

    private int newV(int l, int _suf) {
        if ((n >= len.length)) throw new AssertionError();
        for (int i = 0; i < ALPHA_SIZE; i++) {
            next[n * ALPHA_SIZE + i] = 0;
        }
        len[n] = l;
        suf[n] = _suf;
        return n++;
    }
}