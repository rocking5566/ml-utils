#include "MLControl.h"
#include <fstream>
#include "LibSVMDataWriter.h"
#include "FileIterator.h"
#include "Feature.h"
#include "ImageUtil.h"
#include "opencv2/opencv.hpp"
#include "time.h"
#include "LibSVMPredictResultReader.h"


#define POSITIVE_LABEL 1
#define NEGATIVE_LABEL 2
#define TRAINING_DATA "right_ULSee_all_train_hog_64x128_144_with_left_flip"
#define TESTING_DATA "right_ULSee_all_test_hog_64x128_144"

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

        vector<float>descriptors = Feature::GetHogDescriptor_64x128_144(img);
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


void MLControl::GenerateRandomData(double max, int vecSize, int dataCount)
{
    string sSvmDataPath = (string)TESTING_DATA + "_Random";
    int label = NEGATIVE_LABEL;
    srand(time(NULL));

    CLibSVMDataWriter svmWriter;
    svmWriter.Open(sSvmDataPath);
    vector<double> descriptors;
    descriptors.resize(vecSize);

    for (int i = 0; i < dataCount; ++i)
    {
        for (int j = 0; j < vecSize; ++j)
        {
            descriptors[j] = double(rand() % 1000) * max / 1000;
        }

        svmWriter.WriteBack<double>(label, descriptors);
    }

    svmWriter.Close();
}

void MLControl::IterateImages(const std::string& sImgpath, const std::string& sFilter, EIteratorOperation type)
{
    CFileIterator positiveIter(sImgpath, sFilter);
    int index = 0;
    fstream fp;

    while (positiveIter.FindNext())
    {
        switch (type)
        {
        case eWriteFileName:
            if (index == 0)
            {
                fp.open("right_test_01_Network.txt", ios::out);
                fp << sImgpath << endl;
            }

            fp << index << " - " << positiveIter.FullFileName() << endl;
            break;

        case ePlotHogFeature:
            cout << index << " - " << positiveIter.FullFileName() << endl;
            PlotHogFeature(positiveIter.FullFileName(), eOriginal);
            break;

        default:
            break;
        }

        ++index;
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

void MLControl::CopySVMPredictFalseImage()
{
    CopySVMPredictFalseImage("D:/data/phone talking/positive_right_test_20170703/right_test_02_ULSee"
        , "*.jpg"
        , "D:/data/phone talking/falsePositive/right_test_02_ULSee"
        , "output_file_2");
}

void MLControl::CopySVMPredictFalseImage(const std::string& srcPath, const std::string& sFilter, const std::string& dstPath, const std::string& sSVMPredictResult)
{
    string srcFolder = srcPath;
    string dstFolder = dstPath;
    CLibSVMPredictResultReader reader;
    reader.Open(sSVMPredictResult);
    set<int> setIndex = reader.GetFalseIndex(POSITIVE_LABEL);
    CFileIterator positiveIter(srcFolder, sFilter);
    int index = 0;
    string copyCmd;
    while (positiveIter.FindNext())
    {
        auto iter = setIndex.find(index);
        if (iter != setIndex.end())
        {
            copyCmd = "copy \"" + positiveIter.FullFileName() + "\" \"" + dstFolder + "/" + positiveIter.FileName() + "\"";
            replace(copyCmd.begin(), copyCmd.end(), '/', '\\');
            system(copyCmd.c_str());
        }

        ++index;
    }

    reader.Close();
}
