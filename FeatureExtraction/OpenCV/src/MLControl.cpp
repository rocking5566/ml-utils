#include "MLControl.h"
#include <fstream>
#include "LibSVMDataWriter.h"
#include "FileIterator.h"
#include "Feature.h"
#include "ImageUtil.h"
#include "opencv2/opencv.hpp"

#define POSITIVE_LABEL 1
#define NEGATIVE_LABEL 2
#define TRAINING_DATA "right_ULSee_all_train_hog_32x64_144_with_left_flip"
#define TESTING_DATA "right_ULSee_all_test_hog_32x64_144"

using namespace std;
using namespace cv;

void MLControl::WriteHogToLibSvmFromImg(const std::string& sImgpath, const std::string& sSvmDataPath, const std::string& sFilter, int label, EImageProcess type /*= eOriginal*/)
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

void MLControl::GenerateTrainingData()
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

void MLControl::GenerateTestingData()
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


void MLControl::IterateImages(const std::string& sImgpath, const std::string& sFilter, EIteratorOperation type)
{
    CFileIterator positiveIter(sImgpath, sFilter);
    int index = 1;
    fstream fp;
    fp.open("negative_test_RotateMinrror.txt", ios::out);
    fp << sImgpath << endl;

    while (positiveIter.FindNext())
    {

        switch (type)
        {
        case eWriteFileName:
            fp << index++ << " - " << positiveIter.FullFileName() << endl;
            break;
        case ePlotHogFeature:
            cout << index++ << " - " << positiveIter.FullFileName() << endl;
            PlotHogFeature(positiveIter.FullFileName(), eOriginal);
            break;
        default:
            break;
        }
    }
}

void MLControl::PlotHogFeature(const std::string& sImgpath, EImageProcess type)
{
    double descriptors[144] = { 0 };
    Mat img = imread(sImgpath);

    imshow("img", img);

    if (type == eFlip)
    {
        flip(img, img, 1);
    }

    vector<float>descriptorsVec = Feature::GetHogDescriptor_32x64_144(img);
    std::copy(descriptorsVec.begin(), descriptorsVec.end(), descriptors);
    ImageUtil::PlotVector(descriptors, descriptorsVec.size(), 1);
    waitKey(0);
}
