package video;

/**
 * @author: pashka
 */
public interface VideoSource {

    IndexedImage getNextFrame();

    void setAnswer(int answer, int userId);




}
