#include "opencv2/opencv.hpp"
#include "opencv2/video/background_segm.hpp"
#include <iostream>

using namespace std;
using namespace cv;

int main(int argc, char** argv)
{
    VideoCapture cap(0);
    Mat frame;
    Mat fgMaskMOG2;
    Mat bgMaskMOG2;
    Ptr<BackgroundSubtractor> pMOG2 = createBackgroundSubtractorMOG2();

    while (1)
    {
        Mat obj;

        cap >> frame;
        imshow("frame", frame);

        pMOG2->apply(frame, fgMaskMOG2);
        frame.copyTo(obj, fgMaskMOG2);
        bitwise_not(fgMaskMOG2, bgMaskMOG2);

        imshow("frame", frame);
        imshow("obj", obj);
        imshow("FG Mask MOG 2", fgMaskMOG2);
        imshow("BG Mask MOG 2", bgMaskMOG2);

        if (waitKey(1) == 27)
            break;
    }
}