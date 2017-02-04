package video;

import java.util.*;

/**
 * @author: pashka
 */
public class ButterfliesVideoSource implements VideoSource {

    public static final int WIDTH = 400;
    public static final int HEIGHT = 300;
    public static final int SIZE = 100;
    public static final int ANS_N = 10;
    private final List<IndexedImage>[] butterflies;
    private final int n;
    private final int testN;
    private final IndexedImage image;
    private final boolean animated;
    private final IndexedImage bg;

    Random random = new Random();

    int[] x;
    int[] y;
    int[] t;
    int[] dx;
    int[] dy;

    public ButterfliesVideoSource(List<IndexedImage>[] butterflies, IndexedImage bg, int n, boolean animated, int testN) {
        this.butterflies = butterflies;
        this.bg = bg;
        this.n = n;
        this.animated = animated;
        this.testN = testN;

        image = new IndexedImage(WIDTH, HEIGHT, butterflies[0].get(0).colors);
        x = new int[n];
        y = new int[n];
        dx = new int[n];
        dy = new int[n];
        t = new int[n];
        for (int i = 0; i < n; i++) {
            x[i] = random.nextInt(WIDTH - SIZE);
            y[i] = random.nextInt(HEIGHT - SIZE);
            dx[i] = random.nextInt(21) - 10;
            dy[i] = random.nextInt(21) - 10;
            t[i] = i % butterflies.length;
        }

    }

    int time = 0;

    @Override
    public IndexedImage getNextFrame() {
        image.drawImage(bg, 0, 0);
        for (int i = 0; i < n; i++) {
            x[i] += dx[i];
            y[i] += dy[i];
            if (x[i] >= WIDTH - SIZE) {
                x[i] = WIDTH - SIZE;
                dx[i] = -dx[i];
            }
            if (x[i] <= 0) {
                x[i] = 0;
                dx[i] = -dx[i];
            }
            if (y[i] >= HEIGHT - SIZE) {
                y[i] = HEIGHT - SIZE;
                dy[i] = -dy[i];
            }
            if (y[i] <= 0) {
                y[i] = 0;
                dy[i] = -dy[i];
            }
            List<IndexedImage> butterfly = butterflies[t[i]];
            IndexedImage frame = butterfly.get(animated ? ((time + 5 * i) % butterfly.size()) : 0);
            image.drawImage(
                    frame,
                    x[i], y[i]);
        }
        time++;
        return image;
    }

    Map<Integer, double[]> scoresMap = new HashMap<>();

    @Override
    public void setAnswer(int answer, int userId) {
        double score = answer == 0 ? 0 : 100 * Math.min(1.0 * n / answer, 1.0 * answer / n);
        double[] scores = scoresMap.get(userId);
        if (scores == null) {
            scores = new double[ANS_N];
            Arrays.fill(scores, -1);
            scoresMap.put(userId, scores);
        }
        int i = 0;
        while (i < ANS_N && scores[i] >= 0) i++;
        if (i < ANS_N) {
            scores[i] = answer;
        } else {
            System.arraycopy(scores, 1, scores, 0, ANS_N - 1);
            scores[ANS_N - 1] = score;
        }
        if (scores[ANS_N - 1] >= 0) {
            double s = 0;
            for (double ss : scores) {
                s += ss;
            }
            s /= ANS_N;
            setScore(userId, s);
        }
    }

    private void setScore(int userId, double s) {

    }
}
