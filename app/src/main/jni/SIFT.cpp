//
// Created by BeastQ on 2016/8/29.
//

#include "bupt_edu_dctblock_JniUtils.h"
#include <vector>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/xfeatures2d/nonfree.hpp>
using namespace cv;
using namespace std;
/*
 * Class:     bupt_edu_dctblock_JniUtils
 * Method:    rectifyImg
 * Signature: (JJ)J
 */
JNIEXPORT jlong JNICALL Java_bupt_edu_dctblock_JniUtils_siftRec
  (JNIEnv *env, jclass obj1, jlong modeladdr, jlong srcaddr,jint calSums)
  {
    Mat* model = (Mat*) modeladdr;
    Mat* src = (Mat*) srcaddr;
    Ptr<xfeatures2d::SIFT> feature = xfeatures2d::SIFT::create();
    Mat input1 = *model;
    Mat input2 = *src;
    vector<KeyPoint> keypoints1;

    feature->detect(input1, keypoints1);

    vector<KeyPoint> keypoints2;

    feature->detect(input2, keypoints2);


    /* 下面进行特征向量提取 */

    /************************************************************************/

    Mat description1;

    feature->compute(input1, keypoints1, description1);

    Mat description2;

    feature->compute(input2, keypoints2, description2);


    /************************************************************************/

    /* 下面进行特征向量匹配 */

    /************************************************************************/

    vector<DMatch> matches;

    //FlannBasedMatcher matcher;
    BFMatcher matcher;

    Mat image_match;

    matcher.match(description1, description2, matches);

    /************************************************************************/

    /* 下面进行RANSAC筛选 */

    /************************************************************************/

    vector<Point2f> obj;
    vector<Point2f> scene;

    for (size_t i = 0; i < matches.size(); i++)
    {
        //-- Get the keypoints from the good matches
        obj.push_back(keypoints1[matches[i].queryIdx].pt);
        scene.push_back(keypoints2[matches[i].trainIdx].pt);
    }

    vector<uchar> inliersMask(obj.size());
    Mat H = findHomography(scene, obj, CV_FM_RANSAC, 3.0, inliersMask,calSums);

    Size size = input1.size();
    Mat dstimg = Mat::zeros(size, CV_8UC3);
    warpPerspective(input2, dstimg, H, size);
    Mat *result = new Mat();
    *result = dstimg;
    return (jlong)result;
  }
