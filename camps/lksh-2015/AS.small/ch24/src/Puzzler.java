import javax.imageio.ImageIO;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;
import java.util.Random;

/**
 * @author: pashka
 */
public class Puzzler {

    public static void main(String[] args) throws IOException {
        Random random = new Random();
        for (int picid = 0; picid < 23; picid++) {
            BufferedImage image = ImageIO.read(new File("pics/puzzle/" + (picid + 1) + ".jpg"));
            int height = image.getHeight();
            int width = image.getWidth();
            int nx = 2 + picid / 2;
            int ny = nx * height / width;
            if (ny < 2) ny = 2;
            int n = nx * ny;
            height -= height % ny;
            width -= width % nx;
            BufferedImage result = new BufferedImage(width, height, BufferedImage.TYPE_INT_RGB);
            int[] p = new int[nx * ny];
            while (true) {
                for (int i = 0; i < n; i++) {
                    int j = random.nextInt(i + 1);
                    p[i] = p[j];
                    p[j] = i;
                }
                boolean ok = true;
                for (int i = 0; i < ny; i++) {
                    for (int j = 0; j < nx; j++) {
                        int k = i * nx + j;
                        if (i < ny - 1 && p[k + nx] == p[k] + nx) ok = false;
                        if (j < nx - 1 && p[k + 1] == p[k] + 1) ok =false;
                    }
                }
                if (ok) break;
            }
            int dx = width / nx;
            int dy = height / ny;
            for (int i = 0; i < n; i++) {
                int x = i % nx;
                int y = i / nx;
                int xx = p[i] % nx;
                int yy = p[i] / nx;
                result.getGraphics().drawImage(image, x * dx, y * dy, (x + 1) * dx, (y + 1) * dy,
                        xx * dx, yy * dy, (xx + 1) * dx, (yy + 1) * dy, null);
            }
            ImageIO.write(result, "png", new File("pics/puzzle/" + (picid + 1) + ".png"));
        }
    }
}
