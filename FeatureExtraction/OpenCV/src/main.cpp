#include <iostream>
#include "opencv2/opencv.hpp"
#include "MLControl.h"

using namespace cv;

int main(int argc, char** argv)
{
    MLControl::GenerateTrainingData();
    //MLControl::GenerateTestingData();
}