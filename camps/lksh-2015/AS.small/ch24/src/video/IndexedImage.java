package video;

import java.awt.image.BufferedImage;
import java.awt.image.DataBufferInt;
import java.util.*;
import java.util.List;

/**
 * @author: pashka
 */
public class IndexedImage {
    int width;
    int height;
    int[] colors;
    byte[] pixels;
    boolean[] visible;

    public IndexedImage(BufferedImage image, int[] colors) {
        width = image.getWidth();
        height = image.getHeight();
        this.colors = colors;
        pixels = new byte[width * height];
        visible = new boolean[width * height];
        int[] r = new int[colors.length];
        int[] g = new int[colors.length];
        int[] b = new int[colors.length];
        for (int i = 0; i < colors.length; i++) {
            r[i] = colors[i] & 0xff;
            g[i] = (colors[i] >> 8) & 0xff;
            b[i] = (colors[i] >> 16) & 0xff;
        }
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                int rgb = image.getRGB(x, y);
                pixels[y * width + x] = (byte) getClosest(r, g, b, rgb);
                visible[y * width + x] = (rgb & 0xff000000) != 0;
            }
        }
    }

    public IndexedImage(int width, int height, int[] colors) {
        this.width = width;
        this.height = height;
        this.colors = colors;
        pixels = new byte[width * height];
        visible = new boolean[width * height];
    }

    private static int getClosest(int[] r, int[] g, int[] b, int rgb) {
        int rr = rgb & 0xff;
        int gg = (rgb >> 8) & 0xff;
        int bb = (rgb >> 16) & 0xff;
        return getClosest(r, g, b, rr, gg, bb);
    }

    private static int getClosest(int[] r, int[] g, int[] b, int rr, int gg, int bb) {
        int d = 1000000000;
        int c = 0;
        for (int j = 0; j < r.length; j++) {
            int dd = Math.abs(rr - r[j]) + Math.abs(gg - g[j]) + Math.abs(bb - b[j]);
            if (dd < d) {
                d = dd;
                c = j;
            }
        }
        return c;
    }

    public static int[] getOptimalColors(List<BufferedImage> img, int n) {
        int[] r = new int[n];
        int[] g = new int[n];
        int[] b = new int[n];
        Random random = new Random();
        for (int i = 0; i < n; i++) {
            r[i] = random.nextInt(256);
            g[i] = random.nextInt(256);
            b[i] = random.nextInt(256);
        }
        int[] sr = new int[n];
        int[] sg = new int[n];
        int[] sb = new int[n];
        int[] sn = new int[n];
        int nn = n;

        int[] allpixels = new int[img.get(0).getWidth() * img.get(0).getHeight() * img.size()];
        int ccc = 0;
        for (BufferedImage image : img) {
            int width = image.getWidth();
            if (image.getRaster().getDataBuffer() instanceof DataBufferInt) {
                int[] pixels = ((DataBufferInt) image.getRaster().getDataBuffer()).getData();
                for (int y = 0; y < image.getHeight(); y++) {
                    for (int x = 0; x < image.getWidth(); x++) {
                        allpixels[ccc++] = pixels[y * width + x];
                    }
                }
            }
        }
        Arrays.sort(allpixels);

        for (int i = 0; i < 10; i++) {
            Arrays.fill(sr, 0);
            Arrays.fill(sg, 0);
            Arrays.fill(sb, 0);
            Arrays.fill(sn, 0);
            int last = -1;
            int lastc = 0;
            for (int rgb : allpixels) {
                if ((rgb & 0xff000000) != 0) {
                    int c;
                    if (rgb == last) {
                        c = lastc;
                    } else {
                        c = getClosest(r, g, b, rgb);
                    }
                    int rr = rgb & 0xff;
                    int gg = (rgb >> 8) & 0xff;
                    int bb = (rgb >> 16) & 0xff;
                    sr[c] += rr;
                    sg[c] += gg;
                    sb[c] += bb;
                    sn[c]++;
                    last = rgb;
                    lastc = c;
                }
            }
            nn = 0;
            for (int j = 0; j < n; j++) {
                if (sn[j] > 0) {
                    r[j] = sr[j] / sn[j];
                    g[j] = sg[j] / sn[j];
                    b[j] = sb[j] / sn[j];
                    nn++;
                } else {
                    r[j] = random.nextInt(256);
                    g[j] = random.nextInt(256);
                    b[j] = random.nextInt(256);
                }
            }
        }
        int[] res = new int[nn];
        int j = 0;
        for (int i = 0; i < n; i++)
            if (sn[i] > 0) {
                res[j] = r[i] + (g[i] << 8) + (b[i] << 16);
                j++;
            }
        Arrays.sort(res);
        return res;
    }

    public int getPixel(int x, int y) {
        return pixels[y * width + x];
    }

    public void clear() {
        Arrays.fill(pixels, (byte) 0);
        Arrays.fill(visible, true);
    }

    public IndexedImage scaleTo(int width, int height) {
        IndexedImage res = new IndexedImage(width, height, colors);
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                int xx = x * this.width / width;
                int yy = y * this.height / height;
                int i = y * width + x;
                int j = yy * this.width + xx;
                res.pixels[i] = pixels[j];
                res.visible[i] = visible[j];
            }
        }
        return res;
    }

    public void drawImage(IndexedImage image, int x, int y) {
        for (int i = 0; i < image.height; i++) {
            for (int j = 0; j < image.width; j++) {
                int c = i * image.width + j;
                if (image.visible[c]) {
                    pixels[(y + i) * width + x + j] = image.pixels[c];
                }
            }
        }
    }
}
