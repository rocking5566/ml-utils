#include <iostream>
#include "opencv2/opencv.hpp"
#include "MLControl.h"

using namespace cv;

int main(int argc, char** argv)
{
    MLControl::GenerateTrainingData();
    //MLControl::GenerateTestingData();

    //MLControl::CopySVMPredictFalseImage();


    //MLControl::GenerateRandomData(0.5, 144, 1000);
    //MLControl::IterateImages("D:/data/phone talking/positive_right_test_20170703/right_test_02_ULSee", "*.jpg", ePlotHogFeature);
    //MLControl::IterateImages("D:/data/phone talking/negative_test_RotateMinrror", "*LBP_R.jpg", ePlotHogFeature);
    //MLControl::IterateImages("D:/data/phone talking/positive_right_test_20170703/right_test_01_Network", "*.jpg", eWriteFileName);
//     Mat img = imread("test.jpg");
//     vector<float>descriptors = Feature::GetHogDescriptor_32x64_144(img);
//     cout << descriptors.size() << endl;
//     imshow("test", img);
//     waitKey(0);
}