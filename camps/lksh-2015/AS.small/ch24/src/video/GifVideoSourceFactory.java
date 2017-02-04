package video;

import java.awt.image.BufferedImage;
import java.io.FileInputStream;
import java.io.IOException;
import java.util.List;

/**
 * @author: pashka
 */
public class GifVideoSourceFactory implements VideoSourceFactory{

    IndexedImage[] frames;

    public GifVideoSourceFactory(String filename) throws IOException {
        List<BufferedImage> img = GifDecoder.read(new FileInputStream(filename)).toImages();
        int[] colors = IndexedImage.getOptimalColors(img, 64);
        frames = new IndexedImage[img.size()];
        for (int i = 0; i < frames.length; i++) {
            frames[i] = new IndexedImage(img.get(i), colors);
        }
    }

    @Override
    public VideoSource createVideoSource() {
        try {
            return new GifVideoSource(frames);
        } catch (IOException e) {
            e.printStackTrace();
            return null;
        }
    }
}
