package bupt.edu.opencv_nonfree;

/**
 * Created by BeastQ on 2016/8/29.
 */
public class JniUtils {
    static{
        System.loadLibrary("nonfree");
        System.loadLibrary("opencv_java3");
        System.loadLibrary("SIFT");
    }
    public static native long siftRec(long model,long src,int calSums);
}
