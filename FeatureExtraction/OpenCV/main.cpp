#include "opencv2/opencv.hpp"
#include "Feature.h"
#include "FileIterator.h"
#include "LibSVMDataWriter.h"
#include <iostream>

#define POSITIVE_LABEL 1
#define NEGATIVE_LABEL 2
#define TRAINING_DATA "right_ULSee_all_train_hog_32x64_144_with_left_flip"
#define TESTING_DATA "right_ULSee_all_test_hog_32x64_144"

enum EImageProcess
{
    eOriginal,
    eFlip
};

using namespace std;
using namespace cv;

void WriteHogToLibSvmFromImg(const string& sImgpath, const string& sSvmDataPath, const string& sFilter, int label, EImageProcess type = eOriginal)
{
    cout << "Generate data from " << sImgpath << "/" << sFilter << endl;

    CLibSVMDataWriter svmWriter;
    svmWriter.Open(sSvmDataPath);

    CFileIterator positiveIter(sImgpath, sFilter);
    while (positiveIter.FindNext())
    {
        Mat img = imread(positiveIter.FullFileName());

        if (type == eFlip)
        {
            flip(img, img, 1);
        }

        vector<float>descriptors = Feature::GetHogDescriptor_32x64_144(img);
        svmWriter.WriteBack<float>(label, descriptors);
    }

    svmWriter.Close();
}

void GenerateTrainingData()
{
    cout << "write training data" << endl;
    string sSvmDataPath = TRAINING_DATA;

    // =====================================Positive=================================================
    // 145 images
    WriteHogToLibSvmFromImg("D:/data/phone talking/positive_right_train_20170703_7532/right_ULSee_all_train"
        , sSvmDataPath
        , "*.jpg"
        , POSITIVE_LABEL);

    // 7320 images
    WriteHogToLibSvmFromImg("D:/data/phone talking/positive_right_train_20170703_7532/right_train_7320"
        , sSvmDataPath
        , "*.jpg"
        , POSITIVE_LABEL);

    // 67 images
    WriteHogToLibSvmFromImg("D:/data/phone talking/positive_right_train_20170703_7532/_retrain_CAM_right"
        , sSvmDataPath
        , "*.jpg"
        , POSITIVE_LABEL);

    // 145 images
    WriteHogToLibSvmFromImg("D:/data/phone talking/Mirror_positive_left_train_20170703_7649/left_ULSee_all_train"
        , sSvmDataPath
        , "*.jpg"
        , POSITIVE_LABEL);

    // 7428 images
    WriteHogToLibSvmFromImg("D:/data/phone talking/Mirror_positive_left_train_20170703_7649/left_train_7428"
        , sSvmDataPath
        , "*.jpg"
        , POSITIVE_LABEL);

    // 76 images
    WriteHogToLibSvmFromImg("D:/data/phone talking/Mirror_positive_left_train_20170703_7649/_retrain_CAM_left"
        , sSvmDataPath
        , "*.jpg"
        , POSITIVE_LABEL);

    // =====================================Negative=================================================
    // 8012 images
    WriteHogToLibSvmFromImg("D:/data/phone talking/negative_train_R_8034"
        , sSvmDataPath
        , "*.jpg"
        , NEGATIVE_LABEL);

    // 8012 images - flip
    WriteHogToLibSvmFromImg("D:/data/phone talking/negative_train_L_8034"
        , sSvmDataPath
        , "*.jpg"
        , NEGATIVE_LABEL
        , eFlip);

    // 22 images
    WriteHogToLibSvmFromImg("D:/data/phone talking/negative_train_R_8034/false_alarm"
        , sSvmDataPath
        , "*.jpg"
        , NEGATIVE_LABEL);

    // 22 images - flip
    WriteHogToLibSvmFromImg("D:/data/phone talking/negative_train_L_8034/false_alarm"
        , sSvmDataPath
        , "*.jpg"
        , NEGATIVE_LABEL
        , eFlip);

    // 8 images
    WriteHogToLibSvmFromImg("D:/data/phone talking/negative_train_R_8034/false_alarm/rocking"
        , sSvmDataPath
        , "*.jpg"
        , NEGATIVE_LABEL);
}
void GenerateTestingData()
{
    cout << "write testing data" << endl;

    string sSvmDataPath = TESTING_DATA;

    // =====================================Positive=================================================
    // 3078 images
    WriteHogToLibSvmFromImg("D:/data/phone talking/positive_right_test_20170703/right_test_01_Network"
        , sSvmDataPath + "_1"
        , "*.jpg"
        , POSITIVE_LABEL);

    // 1590 images
    WriteHogToLibSvmFromImg("D:/data/phone talking/positive_right_test_20170703/right_test_02_ULSee"
        , sSvmDataPath + "_2"
        , "*.jpg"
        , POSITIVE_LABEL);

    // 3093 images - flip
    WriteHogToLibSvmFromImg("D:/data/phone talking/positive_left_test_20170703/left_test_01_network"
        , sSvmDataPath + "_3"
        , "*.jpg"
        , POSITIVE_LABEL
        , eFlip);

    // 1590 images - flip
    WriteHogToLibSvmFromImg("D:/data/phone talking/positive_left_test_20170703/left_test_02_ULSee"
        , sSvmDataPath + "_4"
        , "*.jpg"
        , POSITIVE_LABEL
        , eFlip);

    // =====================================Negative=================================================
    // 34105 images
    WriteHogToLibSvmFromImg("D:/data/phone talking/negative_test_CelebFace"
        , sSvmDataPath + "_5"
        , "*LBP_R.jpg"
        , NEGATIVE_LABEL);

    // 11180 images
    WriteHogToLibSvmFromImg("D:/data/phone talking/negative_test_RotateMinrror"
        , sSvmDataPath + "_6"
        , "*LBP_R.jpg"
        , NEGATIVE_LABEL);

    // 34105 images - flip
    WriteHogToLibSvmFromImg("D:/data/phone talking/negative_test_CelebFace"
        , sSvmDataPath + "_7"
        , "*LBP_L.jpg"
        , NEGATIVE_LABEL
        , eFlip);

    // 11180 images - flip
    WriteHogToLibSvmFromImg("D:/data/phone talking/negative_test_RotateMinrror"
        , sSvmDataPath + "_8"
        , "*LBP_L.jpg"
        , NEGATIVE_LABEL
        , eFlip);
}

int main(int argc, char** argv)
{
    GenerateTrainingData();
    GenerateTestingData();

//     Mat img = imread("test.jpg");
//     vector<float>descriptors = Feature::GetHogDescriptor144(img);
//     cout << descriptors.size() << endl;
//     imshow("test", img);
//     waitKey(0);
}