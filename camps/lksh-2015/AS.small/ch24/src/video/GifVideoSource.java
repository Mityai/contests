package video;

import java.io.IOException;

/**
 * @author: pashka
 */
public class GifVideoSource implements VideoSource {

    private final IndexedImage[] frames;

    public GifVideoSource(IndexedImage[] frames) throws IOException {
        this.frames = frames;
    }

    int cur = 0;

    @Override
    public IndexedImage getNextFrame() {
        cur++;
        return frames[cur % frames.length];
    }

    @Override
    public void setAnswer(int answer, int userId) {

    }
}
