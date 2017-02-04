package video;

import javax.imageio.ImageIO;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import java.util.Random;

/**
 * @author: pashka
 */
public class ButterfliesVideoSourceFactory implements VideoSourceFactory{

    private static final int PIC_NUM = 4;
    private final IndexedImage bg;
    private final boolean animated;
    private final int min;
    private final int max;
    private final int testN;

    Random random = new Random();

    List<IndexedImage>[] butterflies;

    public ButterfliesVideoSourceFactory(int min, int max, boolean animated, int testN) throws IOException {
        this.min = min;
        this.max = max;
        this.animated = animated;
        this.testN = testN;
        List<BufferedImage> allImages = new ArrayList<>();
        List<BufferedImage>[] img = new List[PIC_NUM];
        BufferedImage bg = ImageIO.read(new File("pics/field.jpeg"));
//        allImages.add(bg);
        for (int i = 0; i < PIC_NUM; i++) {
            img[i] = GifDecoder.read(new FileInputStream("pics/butterfly" + (i + 1) + ".gif")).toImages();
            allImages.addAll(img[i]);
        }
        int[] colors = IndexedImage.getOptimalColors(allImages, 64);
        this.bg = new IndexedImage(bg, colors).scaleTo(ButterfliesVideoSource.WIDTH, ButterfliesVideoSource.HEIGHT);
        butterflies = new List[PIC_NUM];
        for (int i = 0; i < PIC_NUM; i++) {
            butterflies[i] = new ArrayList<>();
            for (BufferedImage bufferedImage : img[i]) {
                butterflies[i].add(new IndexedImage(bufferedImage, colors).scaleTo(ButterfliesVideoSource.SIZE, ButterfliesVideoSource.SIZE));
            }
        }
    }


    @Override
    public VideoSource createVideoSource() {
        return new ButterfliesVideoSource(butterflies, bg, min + random.nextInt(max - min + 1), animated, testN);
    }
}
