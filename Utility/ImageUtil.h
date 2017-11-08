#ifndef ImageUtil_h__
#define ImageUtil_h__

#include "opencv2/opencv.hpp"

namespace ImageUtil
{
    std::vector<int> CalcHistogram(const unsigned char* srcData, int width, int height, int binCount);
    void ShowRgbImage(const cv::Mat& img);
    void PlotVector(double* hist, int histSize, double upperBound = -1);
};
#endif // ImageUtil_h__