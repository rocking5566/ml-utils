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

void ImageUtil::PlotVector(double* dVec, int vecSize, double upperBound)
{
    int hist_w = 512; int hist_h = 400;
    int bin_w = cvRound((double)hist_w / vecSize);
    Mat histImage(hist_h, hist_w, CV_8UC3, Scalar(0, 0, 0));

    if (upperBound == -1)
    {
        upperBound = *std::max_element(dVec, dVec + vecSize);
        upperBound = upperBound != 0 ? upperBound : 1;
    }

    double scale = double(histImage.rows - 1) / upperBound;

    for (int i = 1; i < vecSize; i++)
    {
        line(histImage, Point(bin_w * (i - 1), hist_h - (dVec[i - 1] * scale)),
            Point(bin_w * i, hist_h - (dVec[i] * scale)),
            Scalar(255, 0, 0), 2, 8, 0);
    }

    imshow("histogram", histImage);
}

