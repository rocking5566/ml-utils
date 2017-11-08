#include <iostream>
#include "MLControl.h"

int main(int argc, char** argv)
{
    MLControl::GenerateTrainingData();
    MLControl::GenerateTestingData();

//     Mat img = imread("test.jpg");
//     vector<float>descriptors = Feature::GetHogDescriptor_32x64_144(img);
//     cout << descriptors.size() << endl;
//     imshow("test", img);
//     waitKey(0);
}