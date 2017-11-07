#include "ImageUtil.h"

using namespace std;
using namespace cv;

std::vector<int> ImageUtil::CalcHistogram(const unsigned char* srcData, int width, int height, int binCount)
{
    vector<int> histogram;
    histogram.resize(binCount);

    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            int ii = i * width;
            ++histogram[*(srcData + ii + j)];
        }
    }

    return std::move(histogram);
}

void ImageUtil::ShowRgbImage(const cv::Mat& img)
{
    Mat channel[3];
    split(img, channel);
    imshow("B", channel[0]);
    imshow("G", channel[1]);
    imshow("R", channel[2]);
}

